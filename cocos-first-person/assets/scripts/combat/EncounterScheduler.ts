import { _decorator, Component, Node, CCInteger, CCBoolean } from 'cc';
import { GameEvents } from '../core/GameEvents';
import { CombatBalance } from '../data/CombatBalance';
import { CombatDirector } from './CombatDirector';

const { ccclass, property } = _decorator;

/** 每 N 次前进触发遭遇（已定稿：前进步数） */
@ccclass('EncounterScheduler')
export class EncounterScheduler extends Component {
  @property(CombatDirector)
  director: CombatDirector | null = null;

  @property(Node)
  eventBus: Node | null = null;

  @property({ type: CCInteger })
  stepsPerEncounter = CombatBalance.stepsPerEncounter;

  @property({ type: CCBoolean })
  enabled = true;

  private stepCount = 0;
  private exploring = true;

  onLoad(): void {
    const bus = this.eventBus ?? this.node;
    bus.on(GameEvents.TUNNEL_STEP_DONE, this.onStep, this);
    bus.on(GameEvents.EXPLORING_DISABLED, () => {
      this.exploring = false;
    });
    bus.on(GameEvents.EXPLORING_ENABLED, () => {
      this.exploring = true;
    });
    bus.on(GameEvents.COMBAT_START, () => {
      this.exploring = false;
    });
    bus.on(GameEvents.COMBAT_END, () => {
      this.exploring = true;
    });
  }

  onDestroy(): void {
    const bus = this.eventBus ?? this.node;
    bus.off(GameEvents.TUNNEL_STEP_DONE, this.onStep, this);
  }

  private onStep(): void {
    if (!this.enabled || !this.exploring) return;
    this.stepCount += 1;
    if (this.stepCount >= this.stepsPerEncounter) {
      this.stepCount = 0;
      this.director?.triggerEncounter();
    }
  }
}
