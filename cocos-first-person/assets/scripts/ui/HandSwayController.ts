import { _decorator, Component, Node, Vec3, tween, Tween, CCFloat } from 'cc';
import { GameEvents } from '../core/GameEvents';

const { ccclass, property } = _decorator;

/**
 * 参考图：前进时左/右手在画面两侧摆动；战斗时可减弱或保持轻摆。
 */
@ccclass('HandSwayController')
export class HandSwayController extends Component {
  @property(Node)
  leftHand: Node | null = null;

  @property(Node)
  rightHand: Node | null = null;

  @property(Node)
  eventBus: Node | null = null;

  @property({ type: CCFloat })
  exploreSwingAngle = 8;

  @property({ type: CCFloat })
  exploreSwingY = 12;

  @property({ type: CCFloat })
  exploreCycleSec = 0.9;

  @property({ type: CCFloat })
  stepSwingBoost = 1.35;

  @property({ type: CCFloat })
  combatSwingAngle = 3;

  private leftOrigin = new Vec3();
  private rightOrigin = new Vec3();
  private leftRotOrigin = 0;
  private rightRotOrigin = 0;
  private mode: 'explore' | 'combat' | 'off' = 'explore';
  private bobTween: Tween<Node> | null = null;

  onLoad(): void {
    if (this.leftHand) {
      this.leftOrigin.set(this.leftHand.position);
      this.leftRotOrigin = this.leftHand.angle;
    }
    if (this.rightHand) {
      this.rightOrigin.set(this.rightHand.position);
      this.rightRotOrigin = this.rightHand.angle;
    }

    const bus = this.eventBus ?? this.node;
    bus.on(GameEvents.TUNNEL_STEP_DONE, this.onStep, this);
    bus.on(GameEvents.COMBAT_START, () => this.setMode('combat'), this);
    bus.on(GameEvents.COMBAT_END, () => this.setMode('explore'), this);
    bus.on(GameEvents.EXPLORING_ENABLED, () => this.setMode('explore'), this);
    bus.on(GameEvents.EXPLORING_DISABLED, () => {}, this);

    this.startExploreBob();
  }

  onDestroy(): void {
    this.bobTween?.stop();
    const bus = this.eventBus ?? this.node;
    bus.off(GameEvents.TUNNEL_STEP_DONE, this.onStep, this);
  }

  private setMode(m: 'explore' | 'combat' | 'off'): void {
    this.mode = m;
    this.startExploreBob();
  }

  private startExploreBob(): void {
    this.bobTween?.stop();
    if (!this.leftHand || !this.rightHand || this.mode === 'off') return;

    const angle = this.mode === 'combat' ? this.combatSwingAngle : this.exploreSwingAngle;
    const dy = this.mode === 'combat' ? this.exploreSwingY * 0.4 : this.exploreSwingY;
    const dur = this.exploreCycleSec;

    const l = this.leftHand;
    const r = this.rightHand;

    this.bobTween = tween(l)
      .to(dur / 2, {
        angle: this.leftRotOrigin - angle,
        position: new Vec3(this.leftOrigin.x, this.leftOrigin.y + dy, this.leftOrigin.z),
      })
      .to(dur / 2, {
        angle: this.leftRotOrigin + angle * 0.5,
        position: this.leftOrigin.clone(),
      })
      .union()
      .repeatForever()
      .start();

    tween(r)
      .to(dur / 2, {
        angle: this.rightRotOrigin + angle,
        position: new Vec3(this.rightOrigin.x, this.rightOrigin.y - dy * 0.6, this.rightOrigin.z),
      })
      .to(dur / 2, {
        angle: this.rightRotOrigin - angle * 0.5,
        position: this.rightOrigin.clone(),
      })
      .union()
      .repeatForever()
      .start();
  }

  /** 每前进一次：双手额外甩一下 */
  private onStep(): void {
    if (this.mode !== 'explore' || !this.leftHand || !this.rightHand) return;
    const boost = this.stepSwingBoost;
    const la = this.exploreSwingAngle * boost;
    const dur = 0.22;

    tween(this.leftHand)
      .to(dur, { angle: this.leftRotOrigin - la })
      .to(dur, { angle: this.leftRotOrigin })
      .start();
    tween(this.rightHand)
      .to(dur, { angle: this.rightRotOrigin + la })
      .to(dur, { angle: this.rightRotOrigin })
      .start();
  }
}
