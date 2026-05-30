import { _decorator, Component, UIOpacity, tween, Node } from 'cc';

const { ccclass, property } = _decorator;

/**
 * 全屏黑场淡入淡出，用于进门、切场景。
 */
@ccclass('FadeOverlay')
export class FadeOverlay extends Component {
  @property(UIOpacity)
  opacityComp: UIOpacity | null = null;

  onLoad(): void {
    if (!this.opacityComp) {
      this.opacityComp = this.getComponent(UIOpacity) ?? this.addComponent(UIOpacity);
    }
    this.opacityComp.opacity = 0;
    this.node.active = true;
  }

  fadeToBlack(durationSec: number): Promise<void> {
    return this.tweenOpacity(255, durationSec);
  }

  fadeFromBlack(durationSec: number): Promise<void> {
    return this.tweenOpacity(0, durationSec);
  }

  private tweenOpacity(target: number, durationSec: number): Promise<void> {
    const op = this.opacityComp!;
    return new Promise((resolve) => {
      tween(op)
        .to(durationSec, { opacity: target }, { easing: 'sineInOut' })
        .call(() => resolve())
        .start();
    });
  }
}
