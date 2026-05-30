import {
  _decorator,
  Component,
  Node,
  Vec3,
  tween,
  director,
  EventTouch,
  UITransform,
  CCFloat,
  CCString,
} from 'cc';
import { GameEvents } from '../core/GameEvents';
import { FadeOverlay } from './FadeOverlay';

const { ccclass, property } = _decorator;

/**
 * 点击左右门：向该点放大 → 黑场 → 切换场景。
 *
 * 节点结构建议：
 * - DoorLeft / DoorRight：带 Button 或本脚本 + UITransform 点击区
 * - focusAnchor：空节点，放在门上（缩放聚焦中心）
 * - zoomTarget：要缩放的节点（通常为 Inner 或 TunnelRoot）
 */
@ccclass('DoorPortal')
export class DoorPortal extends Component {
  @property(Node)
  zoomTarget: Node | null = null;

  /** 缩放聚焦点（门的位置，世界/本地依 parent 而定） */
  @property(Node)
  focusAnchor: Node | null = null;

  @property(FadeOverlay)
  fadeOverlay: FadeOverlay | null = null;

  @property({ type: CCFloat })
  zoomInDuration = 0.45;

  @property({ type: CCFloat })
  zoomScale = 2.2;

  @property({ type: CCFloat })
  fadeDuration = 0.35;

  /** 要加载的场景名（Build Settings 中） */
  @property({ type: CCString })
  nextSceneName = '';

  private busy = false;

  onLoad(): void {
    this.node.on(Node.EventType.TOUCH_END, this.onTap, this);
  }

  private onTap(_e: EventTouch): void {
    if (this.busy || !this.zoomTarget) return;
    this.busy = true;
    this.node.emit(GameEvents.DOOR_ENTER_START);

    const target = this.zoomTarget;
    const startPos = target.position.clone();
    const localFocus = new Vec3();
    if (this.focusAnchor) {
      if (this.focusAnchor.parent === target.parent) {
        localFocus.set(this.focusAnchor.position);
      } else {
        const ui = target.parent?.getComponent(UITransform);
        const world = new Vec3();
        this.focusAnchor.getWorldPosition(world);
        ui?.convertToNodeSpaceAR(world, localFocus);
      }
    }
    const startScale = target.scale.clone();

    tween(target)
      .to(
        this.zoomInDuration,
        {
          position: new Vec3(localFocus.x, localFocus.y, startPos.z),
          scale: new Vec3(
            startScale.x * this.zoomScale,
            startScale.y * this.zoomScale,
            1,
          ),
        },
        { easing: 'cubicIn' },
      )
      .call(() => this.fadeAndLoad(startPos, startScale))
      .start();
  }

  private async fadeAndLoad(restorePos: Vec3, restoreScale: Vec3): Promise<void> {
    const fade = this.fadeOverlay;
    if (fade) await fade.fadeToBlack(this.fadeDuration);

    if (this.nextSceneName) {
      director.loadScene(this.nextSceneName, () => {
        this.node.emit(GameEvents.DOOR_ENTER_DONE);
      });
    } else {
      this.node.emit(GameEvents.DOOR_ENTER_DONE);
    }

    if (fade && !this.nextSceneName) {
      await fade.fadeFromBlack(this.fadeDuration);
      this.zoomTarget?.setPosition(restorePos);
      this.zoomTarget?.setScale(restoreScale);
      this.busy = false;
    }
  }
}
