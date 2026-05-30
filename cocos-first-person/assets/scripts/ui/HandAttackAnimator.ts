import { _decorator, Component, Node, Vec3, tween, CCFloat } from 'cc';

const { ccclass, property } = _decorator;

/** 普攻时右手（或双手）向前挥击的抖动动画（单图手部同理） */
@ccclass('HandAttackAnimator')
export class HandAttackAnimator extends Component {
  @property(Node)
  leftHand: Node | null = null;

  @property(Node)
  rightHand: Node | null = null;

  @property({ type: CCFloat })
  punchForward = 28;

  @property({ type: CCFloat })
  punchDuration = 0.14;

  playAttackSwing(): void {
    const hands = [this.rightHand, this.leftHand].filter(Boolean) as Node[];
    for (const h of hands) {
      const o = h.position.clone();
      const forward = h === this.rightHand ? 1 : -1;
      tween(h)
        .to(this.punchDuration, {
          position: new Vec3(o.x + this.punchForward * forward * 0.15, o.y + 6, o.z),
          angle: h.angle + 10 * forward,
        })
        .to(this.punchDuration, { position: o, angle: h.angle })
        .start();
    }
  }
}
