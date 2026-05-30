import { _decorator, Component, Node, director, CCString } from 'cc';
import { GameEvents } from '../core/GameEvents';

const { ccclass, property } = _decorator;

/**
 * 监听序列最后一帧或自定义事件，加载下一大关场景。
 */
@ccclass('SceneFlowController')
export class SceneFlowController extends Component {
  @property(Node)
  eventBus: Node | null = null;

  @property({ type: CCString })
  nextLevelScene = '';

  onLoad(): void {
    const bus = this.eventBus ?? this.node;
    bus.on(GameEvents.SCENE_FRAME_CHANGED, this.onFrameChanged, this);
  }

  onDestroy(): void {
    const bus = this.eventBus ?? this.node;
    bus.off(GameEvents.SCENE_FRAME_CHANGED, this.onFrameChanged, this);
  }

  private onFrameChanged(detail?: { isLast?: boolean }): void {
    if (detail?.isLast && this.nextLevelScene) {
      director.loadScene(this.nextLevelScene);
    }
  }
}
