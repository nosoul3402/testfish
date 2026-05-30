import { _decorator, Component, Sprite, UITransform, CCFloat } from 'cc';

const { ccclass, property } = _decorator;

/** 玩家技能读条（后期 attack 有 castTime 时显示） */
@ccclass('PlayerCastBarUI')
export class PlayerCastBarUI extends Component {
  @property(Sprite)
  fill: Sprite | null = null;

  @property({ type: CCFloat })
  barWidth = 64;

  private casting = false;
  private elapsed = 0;
  private total = 1;

  update(dt: number): void {
    if (!this.casting || !this.fill) return;
    this.elapsed += dt;
    const p = Math.min(1, this.elapsed / this.total);
    const ui = this.fill.getComponent(UITransform);
    if (ui) ui.width = this.barWidth * p;
    if (p >= 1) this.hide();
  }

  showCast(durationSec: number): void {
    this.total = Math.max(0.05, durationSec);
    this.elapsed = 0;
    this.casting = true;
    this.node.active = true;
    const ui = this.fill?.getComponent(UITransform);
    if (ui) ui.width = 0;
  }

  hide(): void {
    this.casting = false;
    this.node.active = false;
  }
}
