import { _decorator, Component, Node, Label, tween, Vec3, Sprite, Color } from 'cc';

const { ccclass, property } = _decorator;

/**
 * 初期美术：单张 Sprite + 抖动表示动作/受击/施法。
 */
@ccclass('MonsterView')
export class MonsterView extends Component {
  @property(Sprite)
  bodySprite: Sprite | null = null;

  @property(Node)
  zzzRoot: Node | null = null;

  @property(Label)
  zzzLabel: Label | null = null;

  @property(Node)
  castBarRoot: Node | null = null;

  private originPos = new Vec3();
  private shakeTween: ReturnType<typeof tween> | null = null;

  onLoad(): void {
    this.originPos.set(this.node.position);
  }

  setRestingVisible(visible: boolean): void {
    if (this.zzzRoot) this.zzzRoot.active = visible;
    if (this.zzzLabel) this.zzzLabel.string = visible ? 'Z z z' : '';
  }

  setCastBarVisible(visible: boolean): void {
    if (this.castBarRoot) this.castBarRoot.active = visible;
  }

  /** 轻微晃动：走路、待机 */
  playIdleBob(): void {
    this.playShake(3, 4, 0.08);
  }

  /** 攻击/施法释放 */
  playAttackShake(): void {
    this.playShake(8, 12, 0.06);
  }

  /** 受击 */
  playHitFlash(): void {
    this.playShake(14, 18, 0.04);
    if (this.bodySprite) {
      const spr = this.bodySprite;
      const orig = spr.color.clone();
      spr.color = new Color(255, 120, 120, 255);
      this.scheduleOnce(() => {
        spr.color = orig;
      }, 0.12);
    }
  }

  playDeathFade(onDone?: () => void): void {
    tween(this.node)
      .to(0.35, { scale: new Vec3(0.2, 0.2, 1) }, { easing: 'backIn' })
      .call(() => onDone?.())
      .start();
  }

  stopShake(): void {
    this.shakeTween?.stop();
    this.node.setPosition(this.originPos);
  }

  private playShake(freq: number, amp: number, duration: number): void {
    this.shakeTween?.stop();
    const ox = this.originPos.x;
    const oy = this.originPos.y;
    let t = 0;
    this.shakeTween = tween(this.node)
      .repeat(
        Math.ceil(duration / 0.04),
        tween(this.node).call(() => {
          t += 0.04;
          const off = Math.sin(t * freq) * amp;
          this.node.setPosition(ox + off, oy + off * 0.3, this.originPos.z);
        }),
      )
      .call(() => this.node.setPosition(this.originPos))
      .start();
  }
}
