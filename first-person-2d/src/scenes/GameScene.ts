import Phaser from 'phaser';

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
 * 第一人称 2D 主场景：走廊透视 + 前景双手 + 参考图式 HUD / 背包栏。
 * 美术为占位几何图形，后续可替换为精灵图。
 */
export class GameScene extends Phaser.Scene {
  constructor() {
    super({ key: 'GameScene' });
  }

  create(): void {
    const { width, height } = this.scale;
    const viewH = height * 0.58;

    this.drawCorridor(width, viewH);
    this.drawWorldProps(width, viewH);
    this.drawHands(width, height, viewH);
    this.buildTopHud(width);
    this.buildSkillBar(width, viewH);
    this.buildBottomPanel(width, height);
  }

  /** 走廊透视：地板梯形 + 两侧墙 */
  private drawCorridor(w: number, viewH: number): void {
    const g = this.add.graphics();
    g.fillStyle(0x1a1a22, 1);
    g.fillRect(0, 0, w, viewH);

    const cx = w / 2;
    const floorTop = viewH * 0.42;
    const floorBot = viewH * 0.98;

    g.fillStyle(0x2a2830, 1);
    g.beginPath();
    g.moveTo(cx - w * 0.08, floorTop);
    g.lineTo(cx + w * 0.08, floorTop);
    g.lineTo(w, floorBot);
    g.lineTo(0, floorBot);
    g.closePath();
    g.fillPath();

    g.lineStyle(2, 0x3d3848, 0.9);
    for (let i = 0; i < 5; i++) {
      const t = i / 4;
      const y = Phaser.Math.Linear(floorTop, floorBot, t);
      const half = Phaser.Math.Linear(w * 0.08, w * 0.5, t);
      g.lineBetween(cx - half, y, cx + half, y);
    }

    g.fillStyle(0x252530, 1);
    g.fillTriangle(0, 0, cx - w * 0.12, floorTop, 0, viewH);
    g.fillTriangle(w, 0, cx + w * 0.12, floorTop, w, viewH);
  }

  private drawWorldProps(w: number, viewH: number): void {
    const cx = w / 2;
    const chestY = viewH * 0.5;

    const chest = this.add.rectangle(cx, chestY, 36, 28, 0x6b4a2a);
    chest.setStrokeStyle(2, 0x3d2818);
    this.add.rectangle(cx, chestY - 6, 40, 8, 0x8b5a2b);

    const chicken = this.add.ellipse(w * 0.72, viewH * 0.55, 48, 72, 0xf5e6a8);
    chicken.setStrokeStyle(3, 0xc9a227);
    this.add.ellipse(w * 0.72, viewH * 0.42, 22, 26, 0xf5e6a8);
    this.add.triangle(w * 0.78, viewH * 0.4, w * 0.82, viewH * 0.38, w * 0.8, viewH * 0.44, 0xe8a020);
  }

  /** 前景：左手持镜、右手空槽（对应底部高亮装备） */
  private drawHands(w: number, h: number, viewH: number): void {
    const handY = viewH + (h - viewH) * 0.35;

    const leftArm = this.add.rectangle(w * 0.12, handY, 56, 90, 0xc8b8a0, 0.85);
    leftArm.setAngle(-12);
    const mirror = this.add.circle(w * 0.22, handY - 20, 28, 0x8899aa);
    mirror.setStrokeStyle(4, 0xd4af37);
    this.add.circle(w * 0.22, handY - 20, 18, 0xaaccee, 0.4);

    const rightArm = this.add.rectangle(w * 0.88, handY, 56, 90, 0xc8b8a0, 0.85);
    rightArm.setAngle(12);
    this.add.circle(w * 0.78, handY - 10, 24, 0x1a1a1a, 0.9);
    this.add.circle(w * 0.78, handY - 10, 24, 0x555555, 0).setStrokeStyle(3, 0x888888);
  }

  private buildTopHud(w: number): void {
    this.add.text(16, 12, '🪙 300', { fontSize: '18px', color: '#f0d060' });

    const barX = 90;
    const barW = w - 180;
    this.add.rectangle(barX + barW / 2, 22, barW, 10, 0x333340);
    this.add.rectangle(barX + barW * 0.35, 22, barW * 0.35, 8, 0x4a9eff);

    this.add.text(w - 100, 10, '暂停', {
      fontSize: '14px',
      color: '#ccc',
      backgroundColor: '#333',
      padding: { x: 8, y: 4 },
    });
    this.add.text(w - 48, 10, '×2', {
      fontSize: '14px',
      color: '#8cf',
      backgroundColor: '#2a3a4a',
      padding: { x: 6, y: 4 },
    });
  }

  private buildSkillBar(w: number, viewH: number): void {
    const y = viewH + 8;
    const slots = [
      { icon: '🏃', text: '1/2' },
      { icon: '⬆️', text: '1/3' },
      { icon: '💚', text: '8/24' },
    ];
    const startX = w / 2 - 70;
    slots.forEach((s, i) => {
      const x = startX + i * 52;
      this.add.circle(x, y + 24, 22, 0x2a3548).setStrokeStyle(2, 0x556677);
      this.add.text(x, y + 16, s.icon, { fontSize: '16px' }).setOrigin(0.5);
      this.add.text(x, y + 44, s.text, { fontSize: '11px', color: '#aaa' }).setOrigin(0.5);
    });
  }

  private buildBottomPanel(w: number, h: number): void {
    const panelTop = h * 0.58;
    const panel = this.add.rectangle(w / 2, (panelTop + h) / 2, w, h - panelTop, 0x18181e, 0.95);

    const hpY = panelTop + 28;
    this.add.rectangle(w / 2 - 20, hpY, w - 48, 14, 0x3a2020);
    this.add.rectangle(36 + (w - 72) * 0.88 * 0.5, hpY, (w - 72) * 0.88, 12, 0xc04040);
    this.add
      .text(24, hpY - 10, '26196 / 29899', { fontSize: '13px', color: '#f88' })
      .setOrigin(0, 0.5);

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

      this.add.text(x, y - 4, slot.label, { fontSize: '16px', color: '#ddd' }).setOrigin(0.5);
      if (slot.level) {
        this.add
          .text(x, y + 14, `Lv${slot.level}`, { fontSize: '10px', color: '#888' })
          .setOrigin(0.5);
      }
    });

    panel.setDepth(-1);
  }
}
