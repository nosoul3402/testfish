import { _decorator, Component, Node, Vec3, tween, CCFloat, CCBoolean } from 'cc';
import { GameEvents } from '../core/GameEvents';

const { ccclass, property } = _decorator;

/**
 * 第一人称“前进”：中心子图仅放大（锚点已在远处洞口中心），可选同时上移。
 *
 * 美术建议：
 * - 父节点 Frame 用 PNG，左右/上方透明，中间方形洞镂空。
 * - 子节点 Inner 使用同一张或下一层图，position 对准洞口中心，anchor (0.5, 0.5)。
 * - 控制 zoomDuration 即前进速度。
 */
@ccclass('TunnelForwardController')
export class TunnelForwardController extends Component {
  /** 洞口内的嵌套图（会缩放） */
  @property(Node)
  innerTunnel: Node | null = null;

  /** 内层初始缩放（与洞口占画面比例一致，如 0.36） */
  @property({ type: CCFloat })
  innerScaleStart = 0.36;

  /** 单次前进动画时长（秒），越小越快 */
  @property({ type: CCFloat })
  zoomDuration = 0.52;

  /** 是否在放大时向上移动（模拟向走廊深处走） */
  @property({ type: CCBoolean })
  alsoMoveUp = false;

  /** 上移像素（本地坐标，正数向上） */
  @property({ type: CCFloat })
  moveUpDistance = 40;

  @property({ type: CCBoolean })
  blockInputWhileStepping = true;

  /** 事件总线节点（与 TunnelSceneSequence 共用同一节点） */
  @property(Node)
  eventBus: Node | null = null;

  private stepping = false;
  private innerOrigin = new Vec3();

  onLoad(): void {
    if (this.innerTunnel) {
      this.innerOrigin.set(this.innerTunnel.position);
      this.resetInner(false);
    }
  }

  /** 设置前进速度：传入“走完一层”的秒数 */
  setZoomDuration(seconds: number): void {
    this.zoomDuration = Math.max(0.08, seconds);
  }

  /** 点击主区域 / 按钮时调用 */
  stepForward(): void {
    if (!this.innerTunnel || this.stepping) return;
    if (this.blockInputWhileStepping) this.stepping = true;

    const inner = this.innerTunnel;
    const endScale = new Vec3(1, 1, 1);
    const endPos = new Vec3(
      this.innerOrigin.x,
      this.innerOrigin.y + (this.alsoMoveUp ? this.moveUpDistance : 0),
      this.innerOrigin.z,
    );

    tween(inner)
      .to(
        this.zoomDuration,
        {
          scale: endScale,
          position: endPos,
        },
        { easing: 'cubicInOut' },
      )
      .call(() => {
        this.resetInner(true);
        this.stepping = false;
        this.emit(GameEvents.TUNNEL_STEP_DONE);
      })
      .start();
  }

  resetInner(animateEvent: boolean): void {
    if (!this.innerTunnel) return;
    this.innerTunnel.setScale(this.innerScaleStart, this.innerScaleStart, 1);
    this.innerTunnel.setPosition(this.innerOrigin);
    if (animateEvent) {
      // 留给 TunnelSceneSequence 监听 TUNNEL_STEP_DONE
    }
  }

  private emit(event: string): void {
    this.eventBus?.emit(event);
    this.node.emit(event);
  }
}
