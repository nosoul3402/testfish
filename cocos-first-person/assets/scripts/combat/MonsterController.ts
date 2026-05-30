import { _decorator, Component, Node, CCFloat, SpriteFrame } from 'cc';
import { AttackKind, MonsterAttackConfig, MonsterConfigData, MonsterState } from './CombatTypes';
import { MonsterView } from './MonsterView';
import { CastBarUI } from './CastBarUI';
import { CombatBalance } from '../data/CombatBalance';
import { GameEvents } from '../core/GameEvents';

const { ccclass, property } = _decorator;

/**
 * 单怪状态机：休息(zzz) / 走来 / 半即时战斗 / 读条（不可被普攻打断）。
 */
@ccclass('MonsterController')
export class MonsterController extends Component {
  @property(MonsterView)
  view: MonsterView | null = null;

  @property(CastBarUI)
  castBar: CastBarUI | null = null;

  @property(Node)
  eventBus: Node | null = null;

  @property({ type: CCFloat })
  approachDurationSec = 1.2;

  private config: MonsterConfigData | null = null;
  private approachLeft = 0;
  private state: MonsterState = MonsterState.Resting;
  private hp = 0;
  private cooldowns = new Map<string, number>();
  private castAttack: MonsterAttackConfig | null = null;
  private castElapsed = 0;
  private aiTimer = 0;
  private wasRestingOnFirstHit = false;

  get currentState(): MonsterState {
    return this.state;
  }

  get isDead(): boolean {
    return this.state === MonsterState.Dead;
  }

  spawn(config: MonsterConfigData, forceAlert: boolean, bodySprite?: SpriteFrame | null): void {
    this.config = config;
    if (bodySprite) this.view?.setBodySprite(bodySprite);
    this.hp = config.maxHp;
    this.cooldowns.clear();
    this.castAttack = null;
    this.wasRestingOnFirstHit = false;
    this.node.active = true;
    this.node.setScale(1, 1, 1);

    if (forceAlert) {
      this.setState(MonsterState.Approaching);
    } else {
      this.setState(MonsterState.Resting);
    }
  }

  update(dt: number): void {
    if (!this.config || this.isDead) return;

    for (const key of this.cooldowns.keys()) {
      const v = (this.cooldowns.get(key) ?? 0) - dt;
      if (v <= 0) this.cooldowns.delete(key);
      else this.cooldowns.set(key, v);
    }

    if (this.state === MonsterState.Approaching) {
      this.approachLeft -= dt;
      this.view?.playIdleBob();
      if (this.approachLeft <= 0) this.setState(MonsterState.Combat);
      return;
    }

    if (this.state === MonsterState.Casting && this.castAttack) {
      this.castElapsed += dt;
      if (this.castElapsed >= this.castAttack.castTime) {
        this.releaseCast();
      }
      return;
    }

    if (this.state === MonsterState.Combat) {
      this.aiTimer -= dt;
      if (this.aiTimer <= 0) {
        this.aiTimer = 1.1;
        this.pickAndExecuteAttack();
      }
    }
  }

  /** @returns 实际伤害 */
  takePlayerDamage(baseDamage: number, isFirstHit: boolean): number {
    if (!this.config || this.isDead) return 0;

    let mult = 1;
    if (isFirstHit && this.state === MonsterState.Resting) {
      mult = CombatBalance.sneakDamageMultiplier;
      this.wasRestingOnFirstHit = true;
      this.setState(MonsterState.Combat);
    } else if (this.state === MonsterState.Resting) {
      this.setState(MonsterState.Combat);
    }

    const dmg = Math.floor(baseDamage * mult);
    this.hp -= dmg;
    this.view?.playHitShake();
    this.emitState();

    if (this.hp <= 0) {
      this.die();
    }
    return dmg;
  }

  /**
   * 后期：带 Interrupt 标签的玩家技能调用。
   * @returns 是否成功打断
   */
  tryInterruptCast(): boolean {
    if (this.state !== MonsterState.Casting) return false;
    this.castAttack = null;
    this.castBar?.hide();
    this.view?.setCastBarVisible(false);
    this.setState(MonsterState.Combat);
    this.emit(GameEvents.CAST_INTERRUPTED);
    return true;
  }

  private pickAndExecuteAttack(): void {
    if (!this.config) return;
    const pool = this.config.attacks.filter((a) => !this.cooldowns.has(a.id));
    if (!pool.length) return;

    let total = 0;
    for (const a of pool) total += a.weight;
    let roll = Math.random() * total;
    let chosen = pool[0];
    for (const a of pool) {
      roll -= a.weight;
      if (roll <= 0) {
        chosen = a;
        break;
      }
    }

    this.cooldowns.set(chosen.id, chosen.cooldown);

    if (chosen.kind === AttackKind.Skill || chosen.castTime > 0.45) {
      this.startCast(chosen);
    } else {
      this.doInstantAttack(chosen);
    }
  }

  private startCast(attack: MonsterAttackConfig): void {
    this.castAttack = attack;
    this.castElapsed = 0;
    this.setState(MonsterState.Casting);
    this.view?.setCastBarVisible(true);
    this.castBar?.startCast(attack.castTime, attack.kind === AttackKind.Skill);
    this.view?.playIdleBob();
    this.emit(GameEvents.CAST_START, { attackId: attack.id });
  }

  private releaseCast(): void {
    const attack = this.castAttack;
    if (!attack) return;
    this.castAttack = null;
    this.castBar?.hide();
    this.view?.setCastBarVisible(false);
    this.view?.playAttackShake();
    this.setState(MonsterState.Attacking);
    this.emit(GameEvents.CAST_RELEASE, { attackId: attack.id, damage: attack.damage });
    this.scheduleOnce(() => {
      if (this.state === MonsterState.Attacking) this.setState(MonsterState.Combat);
    }, 0.25);
  }

  private doInstantAttack(attack: MonsterAttackConfig): void {
    this.setState(MonsterState.Attacking);
    this.view?.playAttackShake();
    this.emit(GameEvents.CAST_RELEASE, { attackId: attack.id, damage: attack.damage });
    this.scheduleOnce(() => {
      if (this.state === MonsterState.Attacking) this.setState(MonsterState.Combat);
    }, 0.2);
  }

  private die(): void {
    this.setState(MonsterState.Dead);
    this.view?.setRestingVisible(false);
    this.view?.playDeathFade();
  }

  private setState(next: MonsterState): void {
    this.state = next;
    const v = this.view;
    switch (next) {
      case MonsterState.Resting:
        v?.setRestingVisible(true);
        v?.playIdleBob();
        break;
      case MonsterState.Approaching:
        v?.setRestingVisible(false);
        this.approachLeft = this.approachDurationSec;
        break;
      case MonsterState.Combat:
        v?.setRestingVisible(false);
        this.aiTimer = 0.8;
        break;
      case MonsterState.Casting:
        break;
      default:
        break;
    }
    this.emitState();
  }

  private emitState(): void {
    this.emit(GameEvents.MONSTER_STATE_CHANGED, {
      state: this.state,
      hp: this.hp,
      maxHp: this.config?.maxHp,
    });
  }

  private emit(event: string, detail?: unknown): void {
    this.eventBus?.emit(event, detail);
    this.node.emit(event, detail);
  }
}
