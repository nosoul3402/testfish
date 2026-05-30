import Phaser from 'phaser';
import {
  TUNNEL_DEPTH,
  TUNNEL_INNER_RATIO,
  TUNNEL_STEP_MS,
} from './constants';
import {
  buildCorridorFrame,
  buildTunnelEndCap,
} from './buildCorridorFrame';

/**
 * 中心镂空 + 递归嵌套同一画面，前进时各层洞口同步放大，形成隧道纵深。
 */
export class TunnelView {
  private readonly root: Phaser.GameObjects.Container;
  private readonly portals: Phaser.GameObjects.Container[] = [];
  private stepping = false;

  constructor(
    private readonly scene: Phaser.Scene,
    x: number,
    y: number,
    private readonly frameW: number,
    private readonly frameH: number,
  ) {
    this.root = scene.add.container(x, y);
    const outer = this.buildRecursive(TUNNEL_DEPTH);
    this.root.add(outer);
    this.resetPortalScales();

    const hint = scene.add.text(frameW / 2, frameH - 18, '点击画面 · 前进', {
      fontSize: '13px',
      color: '#8899aa',
    });
    hint.setOrigin(0.5, 1);
    this.root.add(hint);

    const hit = scene.add.rectangle(frameW / 2, frameH / 2, frameW, frameH, 0x000000, 0);
    hit.setInteractive({ useHandCursor: true });
    hit.on('pointerdown', () => this.stepForward());
    this.root.add(hit);
    hit.setDepth(1000);
  }

  get displayObject(): Phaser.GameObjects.Container {
    return this.root;
  }

  private buildRecursive(depth: number): Phaser.GameObjects.Container {
    const { container, portal, width, height } = buildCorridorFrame(
      this.scene,
      this.frameW,
      this.frameH,
      { showProps: depth === TUNNEL_DEPTH },
    );

    if (depth > 0) {
      const inner = this.buildRecursive(depth - 1);
      inner.setPosition(-width / 2, -height / 2);
      portal.add(inner);
      this.portals.push(portal);
    } else {
      const cap = buildTunnelEndCap(this.scene, width, height);
      portal.add(cap);
    }

    return container;
  }

  private resetPortalScales(): void {
    for (const portal of this.portals) {
      portal.setScale(TUNNEL_INNER_RATIO);
    }
  }

  stepForward(): void {
    if (this.stepping) return;
    this.stepping = true;

    this.scene.tweens.addCounter({
      from: 0,
      to: 1,
      duration: TUNNEL_STEP_MS,
      ease: 'Cubic.easeInOut',
      onUpdate: (tween) => {
        const t = tween.getValue() ?? 0;
        const scale = Phaser.Math.Linear(
          TUNNEL_INNER_RATIO,
          1,
          t,
        );
        for (const portal of this.portals) {
          portal.setScale(scale);
        }
      },
      onComplete: () => {
        this.resetPortalScales();
        this.stepping = false;
      },
    });
  }
}
