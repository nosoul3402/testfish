import { _decorator, Component, Node, CCInteger, CCBoolean, CCFloat } from 'cc';
import { CombatBalance } from '../data/CombatBalance';
import { DefaultPlayerActions } from '../data/PlayerActionConfig';
import { SkillBarEntry } from '../data/DefaultSkillBar';
import { GameEvents } from '../core/GameEvents';
import { MonsterController } from './MonsterController';
import { SkillTag } from './CombatTypes';
import { SkillAction } from '../ui/SkillTypes';
import { PlayerCastBarUI } from '../ui/PlayerCastBarUI';

const { ccclass, property } = _decorator;

/**
 * 半即时战斗：
 * - 怪物读条/Casting 时，玩家仍可按键（若自己不在读条中）。
 * - 玩家技能可配置 castTimeSec；0 = 即时出手，后期可改为有前摇/读条。
 * - 双方读条并行，互不暂停（除非后期做硬控）。
 */
@ccclass('PlayerCombat')
export class PlayerCombat extends Component {
  @property(MonsterController)
  monster: MonsterController | null = null;

  @property(Node)
  eventBus: Node | null = null;

  @property(PlayerCastBarUI)
  playerCastBar: PlayerCastBarUI | null = null;

  @property({ type: CCInteger })
  baseAttackDamage = 10;

  @property({ type: CCFloat, tooltip: '普攻读条（秒），0=即时；后期可改 0.35 等' })
  normalAttackCastTime = 0;

  @property({ type: CCBoolean })
  debugInterruptSkill = false;

  private hp = CombatBalance.playerMaxHp;
  private inCombat = false;
  private firstHitPending = true;
  private blocking = false;
  private dodgingUntil = 0;
  private acting = false;
  private actionLeft = 0;
  private pendingRelease: (() => void) | null = null;

  onLoad(): void {
    const bus = this.eventBus ?? this.node;
    bus.on(GameEvents.COMBAT_START, this.onCombatStart, this);
    bus.on(GameEvents.COMBAT_END, this.onCombatEnd, this);
    bus.on(GameEvents.CAST_RELEASE, this.onMonsterHitPlayer, this);
  }

  onDestroy(): void {
    const bus = this.eventBus ?? this.node;
    bus.off(GameEvents.COMBAT_START, this.onCombatStart, this);
    bus.off(GameEvents.COMBAT_END, this.onCombatEnd, this);
    bus.off(GameEvents.CAST_RELEASE, this.onMonsterHitPlayer, this);
  }

  get currentHp(): number {
    return this.hp;
  }

  /** 半即时：不在己方读条中即可尝试出手（怪物读条不影响） */
  get canActNow(): boolean {
    return this.inCombat && !this.acting;
  }

  get isActing(): boolean {
    return this.acting;
  }

  update(dt: number): void {
    if (!this.acting || !this.pendingRelease) return;
    this.actionLeft -= dt;
    if (this.actionLeft <= 0) {
      const release = this.pendingRelease;
      this.pendingRelease = null;
      this.acting = false;
      this.playerCastBar?.hide();
      release();
      this.emit(GameEvents.PLAYER_ACTION_RELEASE);
    }
  }

  /** 技能栏统一入口 */
  tryAction(entry: SkillBarEntry): boolean {
    const cast =
      entry.castTimeSec ??
      (entry.action === SkillAction.NormalAttack ? this.normalAttackCastTime : 0) ??
      DefaultPlayerActions[entry.skillId]?.castTimeSec ??
      0;
    const damage =
      entry.damage ??
      DefaultPlayerActions[entry.skillId]?.damage ??
      this.baseAttackDamage;

    switch (entry.action) {
      case SkillAction.NormalAttack:
      case SkillAction.WeaponAttack:
        return this.startPlayerAction(cast, () => this.resolveAttack(damage));
      case SkillAction.Block:
        return this.startPlayerAction(cast, () => this.block());
      case SkillAction.Dodge:
        return this.startPlayerAction(cast, () => this.dodge());
      default:
        return false;
    }
  }

  /** @deprecated 请用 tryAction；保留兼容 */
  normalAttack(): void {
    this.tryAction({
      skillId: 'attack',
      label: '普攻',
      action: SkillAction.NormalAttack,
      castTimeSec: this.normalAttackCastTime,
      damage: this.baseAttackDamage,
    });
  }

  block(): void {
    if (!this.inCombat) return;
    this.blocking = true;
    this.emit('player-block-start');
  }

  dodge(): void {
    if (!this.inCombat) return;
    this.dodgingUntil = Date.now() / 1000 + CombatBalance.dodgeIFrameSec;
    this.emit('player-dodge-start');
  }

  useSkill(tags: number, damage: number): void {
    if (!this.inCombat || !this.monster) return;
    if ((tags & SkillTag.Interrupt) !== 0 && this.monster.tryInterruptCast()) {
      this.emit(GameEvents.CAST_INTERRUPTED);
    }
    if (damage > 0 && !this.monster.isDead) {
      this.monster.takePlayerDamage(damage, false);
      if (this.monster.isDead) this.emit(GameEvents.COMBAT_END, { victory: true });
    }
  }

  debugStunInterrupt(): void {
    this.useSkill(SkillTag.Interrupt | SkillTag.Stun, 0);
  }

  /**
   * 开始己方读条；castSec=0 立即执行。
   * 怪物若在同时读条，双方并行（半即时）。
   */
  private startPlayerAction(castSec: number, onRelease: () => void): boolean {
    if (!this.inCombat) return false;
    if (this.acting) return false;

    if (castSec <= 0) {
      onRelease();
      return true;
    }

    this.acting = true;
    this.actionLeft = castSec;
    this.pendingRelease = onRelease;
    this.playerCastBar?.showCast(castSec);
    this.emit(GameEvents.PLAYER_ACTION_START, { castTimeSec: castSec });
    return true;
  }

  private resolveAttack(damage: number): void {
    if (!this.monster || this.monster.isDead) return;
    const isFirst = this.firstHitPending;
    const dmg = this.monster.takePlayerDamage(damage, isFirst);
    this.firstHitPending = false;
    if (dmg > damage) this.emit('sneak-hit', { damage: dmg });
    if (this.monster.isDead) this.emit(GameEvents.COMBAT_END, { victory: true });
  }

  private onCombatStart(): void {
    this.inCombat = true;
    this.firstHitPending = true;
    this.blocking = false;
    this.dodgingUntil = 0;
    this.acting = false;
    this.pendingRelease = null;
  }

  private onCombatEnd(): void {
    this.inCombat = false;
    this.blocking = false;
    this.acting = false;
    this.pendingRelease = null;
    this.playerCastBar?.hide();
  }

  private onMonsterHitPlayer(ev?: { damage?: number }): void {
    let dmg = ev?.damage ?? 0;
    const now = Date.now() / 1000;
    if (now < this.dodgingUntil) {
      this.emit('player-dodge-success');
      return;
    }
    if (this.blocking) {
      dmg = Math.floor(dmg * CombatBalance.blockDamageRatio);
      this.blocking = false;
      this.emit('player-block-hit', { damage: dmg });
    }
    this.hp = Math.max(0, this.hp - dmg);
    this.emit(GameEvents.PLAYER_HP_CHANGED, { hp: this.hp, max: CombatBalance.playerMaxHp });
    if (this.hp <= 0) this.emit(GameEvents.RUN_RESTART);
  }

  resetForNewRun(): void {
    this.hp = CombatBalance.playerMaxHp;
    this.emit(GameEvents.PLAYER_HP_CHANGED, { hp: this.hp, max: CombatBalance.playerMaxHp });
  }

  private emit(event: string, detail?: unknown): void {
    this.eventBus?.emit(event, detail);
    this.node.emit(event, detail);
  }
}
