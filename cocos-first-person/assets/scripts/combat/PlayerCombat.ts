import { _decorator, Component, Node, CCInteger, CCBoolean } from 'cc';
import { CombatBalance } from '../data/CombatBalance';
import { GameEvents } from '../core/GameEvents';
import { MonsterController } from './MonsterController';
import { SkillTag } from './CombatTypes';

const { ccclass, property } = _decorator;

/**
 * 半即时：读条期间玩家仍可普攻；仅带 Interrupt 的技能可打断读条（后期）。
 */
@ccclass('PlayerCombat')
export class PlayerCombat extends Component {
  @property(MonsterController)
  monster: MonsterController | null = null;

  @property(Node)
  eventBus: Node | null = null;

  @property({ type: CCInteger })
  baseAttackDamage = 10;

  @property({ type: CCBoolean })
  debugInterruptSkill = false;

  private hp = CombatBalance.playerMaxHp;
  private inCombat = false;
  private firstHitPending = true;

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

  /** UI 普攻按钮 */
  normalAttack(): void {
    if (!this.inCombat || !this.monster || this.monster.isDead) return;
    const isFirst = this.firstHitPending;
    const dmg = this.monster.takePlayerDamage(this.baseAttackDamage, isFirst);
    this.firstHitPending = false;
    if (dmg > this.baseAttackDamage) {
      this.emit('sneak-hit', { damage: dmg });
    }
    if (this.monster.isDead) {
      this.emit(GameEvents.COMBAT_END, { victory: true });
    }
  }

  /**
   * 后期技能入口：传入是否含 Interrupt / Stun 标签。
   */
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

  /** 调试：模拟眩晕打断技能 */
  debugStunInterrupt(): void {
    this.useSkill(SkillTag.Interrupt | SkillTag.Stun, 0);
  }

  private onCombatStart(): void {
    this.inCombat = true;
    this.firstHitPending = true;
  }

  private onCombatEnd(): void {
    this.inCombat = false;
  }

  private onMonsterHitPlayer(ev?: { damage?: number }): void {
    const dmg = ev?.damage ?? 0;
    this.hp = Math.max(0, this.hp - dmg);
    this.emit(GameEvents.PLAYER_HP_CHANGED, { hp: this.hp, max: CombatBalance.playerMaxHp });
    if (this.hp <= 0) {
      this.emit(GameEvents.RUN_RESTART);
    }
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
