import { _decorator, Component, Node, Vec3, tween, Enum } from 'cc';
import { GameEvents } from '../core/GameEvents.js';

const { ccclass, property } = _decorator;

export const TunnelForwardMode = Enum({
  ScaleOnly: 0,
  ScaleAndMoveUp: 1,
});

/**
 * JavaScript 版：与 TypeScript 版逻辑相同，二选一使用即可。
 */
@ccclass('TunnelForwardControllerJs')
export class TunnelForwardControllerJs extends Component {
  @property(Node)
  innerTunnel = null;

  @property({ type: TunnelForwardMode })
  forwardMode = TunnelForwardMode.ScaleOnly;

  @property
  innerScaleStart = 0.36;

  @property
  zoomDuration = 0.52;

  @property
  forwardSpeed = 0;

  @property
  moveUpDistance = 40;

  @property
  blockInputWhileStepping = true;

  @property(Node)
  eventBus = null;

  onLoad() {
    this._stepping = false;
    this._innerOrigin = new Vec3();
    if (this.innerTunnel) {
      this._innerOrigin.set(this.innerTunnel.position);
      this.resetInner();
    }
  }

  get stepDuration() {
    if (this.forwardSpeed > 0) {
      return Math.max(0.08, 1.1 / this.forwardSpeed);
    }
    return Math.max(0.08, this.zoomDuration);
  }

  get alsoMoveUp() {
    return this.forwardMode === TunnelForwardMode.ScaleAndMoveUp;
  }

  stepForward() {
    if (!this.innerTunnel || this._stepping) return;
    if (this.blockInputWhileStepping) this._stepping = true;

    const inner = this.innerTunnel;
    const endPos = new Vec3(
      this._innerOrigin.x,
      this._innerOrigin.y + (this.alsoMoveUp ? this.moveUpDistance : 0),
      this._innerOrigin.z,
    );

    tween(inner)
      .to(
        this.stepDuration,
        { scale: new Vec3(1, 1, 1), position: endPos },
        { easing: 'cubicInOut' },
      )
      .call(() => {
        this.resetInner();
        this._stepping = false;
        this._emit(GameEvents.TUNNEL_STEP_DONE);
      })
      .start();
  }

  resetInner() {
    if (!this.innerTunnel) return;
    this.innerTunnel.setScale(this.innerScaleStart, this.innerScaleStart, 1);
    this.innerTunnel.setPosition(this._innerOrigin);
  }

  _emit(event) {
    this.eventBus?.emit?.(event);
    this.node.emit(event);
  }
}
