import { _decorator, Component, Node } from 'cc';
import { GameEvents } from '../core/GameEvents';
import { GameChapterConfig } from './GameChapterConfig';
import { EncounterScheduler } from '../combat/EncounterScheduler';

const { ccclass, property } = _decorator;

/**
 * 关卡总控：把策划配置同步到遭遇、大门等子系统。
 */
@ccclass('GameFlowController')
export class GameFlowController extends Component {
  @property(GameChapterConfig)
  chapter: GameChapterConfig | null = null;

  @property(EncounterScheduler)
  encounterScheduler: EncounterScheduler | null = null;

  @property(Node)
  eventBus: Node | null = null;

  onLoad(): void {
    this.syncChapterConfig();
    const bus = this.eventBus ?? this.node;
    bus.on(GameEvents.GATE_REVEALED, this.onGateRevealed, this);
    bus.on(GameEvents.COMBAT_END, this.onCombatEnd, this);
  }

  onDestroy(): void {
    const bus = this.eventBus ?? this.node;
    bus.off(GameEvents.GATE_REVEALED, this.onGateRevealed, this);
    bus.off(GameEvents.COMBAT_END, this.onCombatEnd, this);
  }

  private syncChapterConfig(): void {
    const cfg = this.chapter;
    if (!cfg || !this.encounterScheduler) return;
    this.encounterScheduler.stepsPerEncounter = cfg.stepsPerEncounter;
  }

  private onGateRevealed(): void {
    if (this.chapter?.stopEncountersAfterGate && this.encounterScheduler) {
      this.encounterScheduler.enabled = false;
    }
  }

  private onCombatEnd(ev?: { victory?: boolean }): void {
    if (ev?.victory) {
      this.emit(GameEvents.MONSTER_DEFEATED);
    }
  }

  private emit(event: string): void {
    this.eventBus?.emit(event);
    this.node.emit(event);
  }
}
