import { _decorator, Component, Node, input, Input, EventTouch, KeyCode } from 'cc';
import { TunnelForwardController } from './TunnelForwardController';

const { ccclass, property } = _decorator;

/** 点击主画面或空格/W 触发前进 */
@ccclass('TunnelTapArea')
export class TunnelTapArea extends Component {
  @property(TunnelForwardController)
  tunnel: TunnelForwardController | null = null;

  onLoad(): void {
    this.node.on(Node.EventType.TOUCH_END, this.onTap, this);
    input.on(Input.EventType.KEY_DOWN, this.onKey, this);
  }

  onDestroy(): void {
    input.off(Input.EventType.KEY_DOWN, this.onKey, this);
  }

  private onTap(_e: EventTouch): void {
    this.tunnel?.stepForward();
  }

  private onKey(e: { keyCode: KeyCode }): void {
    if (e.keyCode === KeyCode.SPACE || e.keyCode === KeyCode.KEY_W) {
      this.tunnel?.stepForward();
    }
  }
}
