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
    bus.on('skill-card-click', this.onCardClick, this);
  }

  onDestroy(): void {
    const bus = this.eventBus ?? this.node;
    bus.off(GameEvents.COMBAT_START, this.show, this);
    bus.off(GameEvents.COMBAT_END, this.hide, this);
    bus.off('skill-card-click', this.onCardClick, this);
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

  private onCardClick(detail?: { action?: SkillAction }): void {
    const player = this.player;
    if (!player) return;
    switch (detail?.action) {
      case SkillAction.NormalAttack:
      case SkillAction.WeaponAttack:
        this.handAttack?.playAttackSwing();
        player.normalAttack();
        break;
      case SkillAction.Block:
        player.block();
        break;
      case SkillAction.Dodge:
        player.dodge();
        break;
      default:
        break;
    }
  }
}
