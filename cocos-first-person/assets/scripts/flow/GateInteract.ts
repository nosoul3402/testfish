import { _decorator, Component, Node, director, EventTouch } from 'cc';
import { GameEvents } from '../core/GameEvents';
import { GameChapterConfig } from './GameChapterConfig';
import { TunnelChapterController } from './TunnelChapterController';

const { ccclass, property } = _decorator;

/** 隧道尽头大门：点击后进入城镇场景 */
@ccclass('GateInteract')
export class GateInteract extends Component {
  @property(GameChapterConfig)
  chapter: GameChapterConfig | null = null;

  @property(TunnelChapterController)
  tunnelChapter: TunnelChapterController | null = null;

  @property(Node)
  eventBus: Node | null = null;

  onLoad(): void {
    this.node.on(Node.EventType.TOUCH_END, this.onTap, this);
    this.node.active = false;
    const bus = this.eventBus ?? this.node;
    bus.on(GameEvents.GATE_REVEALED, this.onGateRevealed, this);
  }

  onDestroy(): void {
    const bus = this.eventBus ?? this.node;
    bus.off(GameEvents.GATE_REVEALED, this.onGateRevealed, this);
  }

  private onGateRevealed(): void {
    // 真正可点由 TunnelChapterController 控制 stepsAfterGateToEnter
  }

  private onTap(_e: EventTouch): void {
    if (!this.tunnelChapter?.gateRevealed) return;
    const scene = this.chapter?.townSceneName ?? 'Town';
    this.emit(GameEvents.GATE_ENTER_REQUEST);
    this.emit(GameEvents.ENTER_TOWN);
    director.loadScene(scene);
  }

  private emit(event: string): void {
    this.eventBus?.emit(event);
    this.node.emit(event);
  }
}
