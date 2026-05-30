import Phaser from 'phaser';
import { TunnelView } from '../tunnel/TunnelView';

/** 装备槽占位数据 */
interface InventorySlot {
  label: string;
  level?: number;
  equipped?: boolean;
}

const INVENTORY: InventorySlot[] = [
  { label: '鸡', level: 1, equipped: true },
  { label: '盔', level: 52 },
  { label: '甲', level: 52 },
  { label: '袍', level: 46 },
  { label: '镜', equipped: true },
  { label: '葫', level: 41 },
  { label: '腿', level: 48 },
  { label: '靴', level: 48 },
];

/**
 * 主场景：递归隧道第一人称视野 + 双手与 HUD（参考移动端地牢布局）。
 */
export class GameScene extends Phaser.Scene {
  private tunnel?: TunnelView;

  constructor() {
    super({ key: 'GameScene' });
  }

  create(): void {
    const { width, height } = this.scale;
    const viewH = height * 0.58;

    this.tunnel = new TunnelView(this, 0, 0, width, viewH);
    this.tunnel.displayObject.setDepth(0);

    this.drawHands(width, height, viewH);
    this.buildTopHud(width);
    this.buildSkillBar(width, viewH);
    this.buildBottomPanel(width, height);

    this.input.keyboard?.on('keydown-SPACE', () => this.tunnel?.stepForward());
    this.input.keyboard?.on('keydown-W', () => this.tunnel?.stepForward());
  }

  /** 前景：左手持镜、右手空槽（不参与隧道递归） */
  private drawHands(w: number, h: number, viewH: number): void {
    const handY = viewH + (h - viewH) * 0.35;
    const depth = 50;

    const leftArm = this.add.rectangle(w * 0.12, handY, 56, 90, 0xc8b8a0, 0.85);
    leftArm.setAngle(-12);
    leftArm.setDepth(depth);
    const mirror = this.add.circle(w * 0.22, handY - 20, 28, 0x8899aa);
    mirror.setStrokeStyle(4, 0xd4af37);
    mirror.setDepth(depth + 1);
    this.add.circle(w * 0.22, handY - 20, 18, 0xaaccee, 0.4).setDepth(depth + 1);

    const rightArm = this.add.rectangle(w * 0.88, handY, 56, 90, 0xc8b8a0, 0.85);
    rightArm.setAngle(12);
    rightArm.setDepth(depth);
    const rightSlot = this.add.circle(w * 0.78, handY - 10, 24, 0x1a1a1a, 0.9);
    rightSlot.setStrokeStyle(3, 0x888888);
    rightSlot.setDepth(depth + 1);
  }

  private buildTopHud(w: number): void {
    const d = 60;
    this.add.text(16, 12, '🪙 300', { fontSize: '18px', color: '#f0d060' }).setDepth(d);

    const barX = 90;
    const barW = w - 180;
    this.add.rectangle(barX + barW / 2, 22, barW, 10, 0x333340).setDepth(d);
    this.add.rectangle(barX + barW * 0.35, 22, barW * 0.35, 8, 0x4a9eff).setDepth(d + 1);

    this.add
      .text(w - 100, 10, '暂停', {
        fontSize: '14px',
        color: '#ccc',
        backgroundColor: '#333',
        padding: { x: 8, y: 4 },
      })
      .setDepth(d);
    this.add
      .text(w - 48, 10, '×2', {
        fontSize: '14px',
        color: '#8cf',
        backgroundColor: '#2a3a4a',
        padding: { x: 6, y: 4 },
      })
      .setDepth(d);
  }

  private buildSkillBar(w: number, viewH: number): void {
    const y = viewH + 8;
    const d = 55;
    const slots = [
      { icon: '🏃', text: '1/2' },
      { icon: '⬆️', text: '1/3' },
      { icon: '💚', text: '8/24' },
    ];
    const startX = w / 2 - 70;
    slots.forEach((s, i) => {
      const x = startX + i * 52;
      this.add.circle(x, y + 24, 22, 0x2a3548).setStrokeStyle(2, 0x556677).setDepth(d);
      this.add.text(x, y + 16, s.icon, { fontSize: '16px' }).setOrigin(0.5).setDepth(d + 1);
      this.add
        .text(x, y + 44, s.text, { fontSize: '11px', color: '#aaa' })
        .setOrigin(0.5)
        .setDepth(d + 1);
    });
  }

  private buildBottomPanel(w: number, h: number): void {
    const panelTop = h * 0.58;
    const d = 40;
    this.add
      .rectangle(w / 2, (panelTop + h) / 2, w, h - panelTop, 0x18181e, 0.95)
      .setDepth(d);

    const hpY = panelTop + 28;
    this.add.rectangle(w / 2 - 20, hpY, w - 48, 14, 0x3a2020).setDepth(d + 1);
    this.add
      .rectangle(36 + (w - 72) * 0.88 * 0.5, hpY, (w - 72) * 0.88, 12, 0xc04040)
      .setDepth(d + 2);
    this.add
      .text(24, hpY - 10, '26196 / 29899', { fontSize: '13px', color: '#f88' })
      .setOrigin(0, 0.5)
      .setDepth(d + 3);

    const gridTop = panelTop + 52;
    const cell = 44;
    const gap = 6;
    const cols = 4;
    const gridW = cols * cell + (cols - 1) * gap;
    const startX = (w - gridW) / 2 + cell / 2;

    INVENTORY.forEach((slot, i) => {
      const col = i % cols;
      const row = Math.floor(i / cols);
      const x = startX + col * (cell + gap);
      const y = gridTop + row * (cell + gap) + cell / 2;

      const bg = this.add.rectangle(x, y, cell, cell, 0x252530);
      bg.setStrokeStyle(slot.equipped ? 3 : 1, slot.equipped ? 0xff8800 : 0x444455);
      bg.setDepth(d + 1);

      this.add
        .text(x, y - 4, slot.label, { fontSize: '16px', color: '#ddd' })
        .setOrigin(0.5)
        .setDepth(d + 2);
      if (slot.level) {
        this.add
          .text(x, y + 14, `Lv${slot.level}`, { fontSize: '10px', color: '#888' })
          .setOrigin(0.5)
          .setDepth(d + 2);
      }
    });
  }
}
