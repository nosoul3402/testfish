import { _decorator, Component, UITransform, Sprite, Color, CCFloat } from 'cc';

const { ccclass, property } = _decorator;

/** 怪物技能读条（普攻不显示或极短） */
@ccclass('CastBarUI')
export class CastBarUI extends Component {
  @property(Sprite)
  fill: Sprite | null = null;

  @property({ type: CCFloat })
  barWidth = 80;

  private casting = false;
  private elapsed = 0;
  private total = 1;

  update(dt: number): void {
    if (!this.casting || !this.fill) return;
    this.elapsed += dt;
    const p = Math.min(1, this.elapsed / this.total);
    const ui = this.fill.getComponent(UITransform);
    if (ui) ui.width = this.barWidth * p;
    if (p >= 1) this.casting = false;
  }

  startCast(durationSec: number, danger = false): void {
    this.total = Math.max(0.1, durationSec);
    this.elapsed = 0;
    this.casting = true;
    this.node.active = true;
    if (this.fill) {
      this.fill.color = danger ? new Color(255, 90, 60, 255) : new Color(120, 180, 255, 255);
      const ui = this.fill.getComponent(UITransform);
      if (ui) ui.width = 0;
    }
  }

  hide(): void {
    this.casting = false;
    this.node.active = false;
  }
}
