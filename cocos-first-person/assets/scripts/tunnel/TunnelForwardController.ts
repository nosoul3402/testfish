import {
  _decorator,
  Component,
  Node,
  Vec3,
  tween,
  CCFloat,
  CCBoolean,
  Enum,
} from 'cc';
import { GameEvents } from '../core/GameEvents';
import { TunnelForwardMode } from './TunnelForwardMode';

const { ccclass, property } = _decorator;

/**
 * 小程序第一人称「前进」—— Cocos Creator 3.x（TypeScript）
 *
 * 做法：Inner 节点锚点 (0.5,0.5) 放在美术洞口中心，只 tween scale（可选上移）。
 * 调 zoomDuration 或 forwardSpeed 控制走路快慢。
 */
@ccclass('TunnelForwardController')
export class TunnelForwardController extends Component {
  @property(Node)
  innerTunnel: Node | null = null;

  @property({ type: Enum(TunnelForwardMode) })
  forwardMode: TunnelForwardMode = TunnelForwardMode.ScaleOnly;

  @property({ type: CCFloat, tooltip: '内层初始缩放，与洞口占屏比例一致' })
  innerScaleStart = 0.36;

  @property({ type: CCFloat, tooltip: '单次前进时长（秒），越小越快' })
  zoomDuration = 0.52;

  @property({ type: CCFloat, tooltip: '1~10，越大越快（会覆盖 zoomDuration）' })
  forwardSpeed = 0;

  @property({ type: CCFloat, tooltip: 'ScaleAndMoveUp 时 Y 方向位移' })
  moveUpDistance = 40;

  @property({ type: CCBoolean })
  blockInputWhileStepping = true;

  @property(Node)
  eventBus: Node | null = null;

  private stepping = false;
  private innerOrigin = new Vec3();

  onLoad(): void {
    if (this.innerTunnel) {
      this.innerOrigin.set(this.innerTunnel.position);
      this.resetInner();
    }
  }

  get alsoMoveUp(): boolean {
    return this.forwardMode === TunnelForwardMode.ScaleAndMoveUp;
  }

  /** 有效动画时长 */
  get stepDuration(): number {
    if (this.forwardSpeed > 0) {
      return Math.max(0.08, 1.1 / this.forwardSpeed);
    }
    return Math.max(0.08, this.zoomDuration);
  }

  setZoomDuration(seconds: number): void {
    this.zoomDuration = Math.max(0.08, seconds);
    this.forwardSpeed = 0;
  }

  setForwardSpeed(speed1to10: number): void {
    this.forwardSpeed = Math.min(10, Math.max(1, speed1to10));
  }

  stepForward(): void {
    if (!this.innerTunnel || this.stepping) return;
    if (this.blockInputWhileStepping) this.stepping = true;

    const inner = this.innerTunnel;
    const duration = this.stepDuration;
    const endScale = new Vec3(1, 1, 1);
    const endPos = new Vec3(
      this.innerOrigin.x,
      this.innerOrigin.y + (this.alsoMoveUp ? this.moveUpDistance : 0),
      this.innerOrigin.z,
    );

    tween(inner)
      .to(duration, { scale: endScale, position: endPos }, { easing: 'cubicInOut' })
      .call(() => {
        this.resetInner();
        this.stepping = false;
        this.emit(GameEvents.TUNNEL_STEP_DONE);
      })
      .start();
  }

  resetInner(): void {
    if (!this.innerTunnel) return;
    this.innerTunnel.setScale(this.innerScaleStart, this.innerScaleStart, 1);
    this.innerTunnel.setPosition(this.innerOrigin);
  }

  private emit(event: string): void {
    this.eventBus?.emit(event);
    this.node.emit(event);
  }
}
