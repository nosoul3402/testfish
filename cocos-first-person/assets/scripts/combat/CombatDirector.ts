import { _decorator, Component, Node, CCBoolean } from 'cc';
import { GameEvents } from '../core/GameEvents';
import { CombatBalance } from '../data/CombatBalance';
import { DefaultSlime } from '../data/DefaultMonsters';
import { MonsterConfigData } from './CombatTypes';
import { MonsterController } from './MonsterController';
import { PlayerCombat } from './PlayerCombat';

const { ccclass, property } = _decorator;

@ccclass('CombatDirector')
export class CombatDirector extends Component {
  @property(MonsterController)
  monster: MonsterController | null = null;

  @property(PlayerCombat)
  player: PlayerCombat | null = null;

  @property(Node)
  monsterSlot: Node | null = null;

  @property(Node)
  eventBus: Node | null = null;

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

  /** 由 EncounterScheduler 调用 */
  triggerEncounter(config: MonsterConfigData = DefaultSlime): void {
    if (this.combatActive) return;
    this.combatActive = true;
    this.emit(GameEvents.EXPLORING_DISABLED);
    this.emit(GameEvents.ENCOUNTER_START, { monsterId: config.id });

    const forceAlert = Math.random() < CombatBalance.earlyAlertChance;
    this.monster?.spawn(config, forceAlert);
    if (this.monsterSlot) this.monsterSlot.active = true;

    this.emit(GameEvents.COMBAT_START, { monsterId: config.id, forceAlert });
  }

  private onEncounterStart(): void {
    // 遭遇短停顿可在此加 tween
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
