import { _decorator, Component, Node, CCBoolean, SpriteFrame } from 'cc';
import { GameEvents } from '../core/GameEvents';
import { CombatBalance } from '../data/CombatBalance';
import { DefaultSlime } from '../data/DefaultMonsters';
import { MonsterConfigData } from './CombatTypes';
import { MonsterController } from './MonsterController';
import { PlayerCombat } from './PlayerCombat';
import { MonsterModelRegistry } from './MonsterModelRegistry';

const { ccclass, property } = _decorator;

@ccclass('CombatDirector')
export class CombatDirector extends Component {
  @property(MonsterController)
  monster: MonsterController | null = null;

  @property(PlayerCombat)
  player: PlayerCombat | null = null;

  @property(MonsterModelRegistry)
  modelRegistry: MonsterModelRegistry | null = null;

  @property(Node)
  monsterSlot: Node | null = null;

  @property(Node)
  eventBus: Node | null = null;

  @property({ type: CCBoolean, tooltip: 'true=从模型表随机；false=仅用 defaultConfig' })
  useRandomMonsterModel = true;

  @property({ type: CCBoolean })
  combatActive = false;

  onLoad(): void {
    const bus = this.eventBus ?? this.node;
    bus.on(GameEvents.ENCOUNTER_START, this.onEncounterStart, this);
    bus.on(GameEvents.COMBAT_END, this.onCombatEnd, this);
  }

  onDestroy(): void {
    const bus = this.eventBus ?? this.node;
    bus.off(GameEvents.ENCOUNTER_START, this.onEncounterStart, this);
    bus.off(GameEvents.COMBAT_END, this.onCombatEnd, this);
  }

  triggerEncounter(fixedConfig?: MonsterConfigData): void {
    if (this.combatActive) return;
    this.combatActive = true;
    this.emit(GameEvents.EXPLORING_DISABLED);

    let config = fixedConfig ?? DefaultSlime;
    let sprite = null as import('cc').SpriteFrame | null;
    let modelId = config.id;

    if (this.useRandomMonsterModel && this.modelRegistry) {
      const pick = this.modelRegistry.pickRandom();
      config = pick.config;
      sprite = pick.spriteFrame;
      modelId = pick.modelId;
    }

    this.emit(GameEvents.ENCOUNTER_START, { monsterId: modelId });

    const forceAlert = Math.random() < CombatBalance.earlyAlertChance;
    this.monster?.spawn(config, forceAlert, sprite);
    if (this.monsterSlot) this.monsterSlot.active = true;

    this.emit(GameEvents.COMBAT_START, { monsterId: modelId, forceAlert });
  }

  private onEncounterStart(): void {
    // 遭遇短停顿
  }

  private onCombatEnd(ev?: { victory?: boolean }): void {
    if (!this.combatActive) return;
    this.combatActive = false;
    this.emit(GameEvents.ENCOUNTER_END, ev);
    this.emit(GameEvents.EXPLORING_ENABLED);
    if (ev?.victory && this.monsterSlot) {
      this.scheduleOnce(() => {
        this.monsterSlot!.active = false;
      }, 0.4);
    }
  }

  private emit(event: string, detail?: unknown): void {
    this.eventBus?.emit(event, detail);
    this.node.emit(event, detail);
  }
}
