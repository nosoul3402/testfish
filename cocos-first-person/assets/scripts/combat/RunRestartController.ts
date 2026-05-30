import { _decorator, Component, director, Node, CCString } from 'cc';
import { GameEvents } from '../core/GameEvents';
import { CombatBalance } from '../data/CombatBalance';
import { PlayerCombat } from './PlayerCombat';

const { ccclass, property } = _decorator;

/**
 * 杀戮尖塔式：HP 归零 → 整局重来（重载起始场景）。
 */
@ccclass('RunRestartController')
export class RunRestartController extends Component {
  @property(Node)
  eventBus: Node | null = null;

  @property(PlayerCombat)
  player: PlayerCombat | null = null;

  @property({ type: CCString })
  startSceneName = CombatBalance.runStartScene;

  onLoad(): void {
    const bus = this.eventBus ?? this.node;
    bus.on(GameEvents.RUN_RESTART, this.restartRun, this);
  }

  onDestroy(): void {
    const bus = this.eventBus ?? this.node;
    bus.off(GameEvents.RUN_RESTART, this.restartRun, this);
  }

  restartRun(): void {
    this.player?.resetForNewRun();
    director.loadScene(this.startSceneName);
  }
}
