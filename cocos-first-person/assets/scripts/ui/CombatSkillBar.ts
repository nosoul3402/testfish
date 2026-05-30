import { _decorator, Component, Node, Prefab, instantiate, CCFloat } from 'cc';
import { GameEvents } from '../core/GameEvents';
import { DefaultSkillBarLayout } from '../data/DefaultSkillBar';
import { SkillCard } from './SkillCard';
import { SkillAction } from './SkillTypes';
import { PlayerCombat } from '../combat/PlayerCombat';
import { HandAttackAnimator } from './HandAttackAnimator';

const { ccclass, property } = _decorator;

/**
 * 遇怪时显示屏幕底部技能卡（格挡 / 闪避 / 普攻 / 空手展示）。
 */
@ccclass('CombatSkillBar')
export class CombatSkillBar extends Component {
  @property(Node)
  barRoot: Node | null = null;

  @property(Prefab)
  cardPrefab: Prefab | null = null;

  @property(PlayerCombat)
  player: PlayerCombat | null = null;

  @property(HandAttackAnimator)
  handAttack: HandAttackAnimator | null = null;

  @property(Node)
  eventBus: Node | null = null;

  @property({ type: CCFloat })
  slideUpOffset = 0;

  private cards: SkillCard[] = [];

  onLoad(): void {
    const root = this.barRoot ?? this.node;
    root.active = false;
    this.buildCards(root);

    const bus = this.eventBus ?? this.node;
    bus.on(GameEvents.COMBAT_START, this.show, this);
    bus.on(GameEvents.COMBAT_END, this.hide, this);
  }

  onDestroy(): void {
    const bus = this.eventBus ?? this.node;
    bus.off(GameEvents.COMBAT_START, this.show, this);
    bus.off(GameEvents.COMBAT_END, this.hide, this);
  }

  private buildCards(root: Node): void {
    if (this.cardPrefab) {
      for (const entry of DefaultSkillBarLayout) {
        const n = instantiate(this.cardPrefab);
        root.addChild(n);
        const card = n.getComponent(SkillCard);
        if (card) {
          card.configure(entry);
          n.on('skill-card-click', this.onCardClick, this);
          this.cards.push(card);
        }
      }
      return;
    }
    const existing = root.getComponentsInChildren(SkillCard);
    if (existing.length) {
      existing.forEach((c, i) => {
        const entry = DefaultSkillBarLayout[i];
        if (entry) c.configure(entry);
        c.node.on('skill-card-click', this.onCardClick, this);
        this.cards.push(c);
      });
    }
  }

  private show(): void {
    const root = this.barRoot ?? this.node;
    root.active = true;
    this.cards.forEach((c) => c.refreshVisual());
  }

  private hide(): void {
    const root = this.barRoot ?? this.node;
    root.active = false;
  }

  private onCardClick(detail?: { skillId?: string; action?: SkillAction }): void {
    const player = this.player;
    if (!player || !player.canActNow) return;

    const entry = DefaultSkillBarLayout.find(
      (e) => e.skillId === detail?.skillId || e.action === detail?.action,
    );
    if (!entry) return;

    const cast = entry.castTimeSec ?? 0;

    if (
      entry.action === SkillAction.NormalAttack ||
      entry.action === SkillAction.WeaponAttack
    ) {
      if (cast <= 0) this.handAttack?.playAttackSwing();
      else {
        const bus = this.eventBus ?? this.node;
        const onRelease = (): void => {
          bus.off(GameEvents.PLAYER_ACTION_RELEASE, onRelease, this);
          this.handAttack?.playAttackSwing();
        };
        bus.on(GameEvents.PLAYER_ACTION_RELEASE, onRelease, this);
      }
    }

    player.tryAction(entry);
  }
}
