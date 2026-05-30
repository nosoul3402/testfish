import Phaser from 'phaser';
import { TUNNEL_INNER_RATIO } from './constants';

export interface CorridorFrameResult {
  /** 当前层整帧（含墙、地板、洞口边框） */
  container: Phaser.GameObjects.Container;
  /** 中心洞口，用于挂载下一层（子帧尺寸与当前帧相同，由 scale 缩小） */
  portal: Phaser.GameObjects.Container;
  width: number;
  height: number;
}

/**
 * 绘制单层走廊画面：四周墙 + 透视地板，中心为正方形洞口；
 * 洞口内由调用方挂载缩小的同名帧，形成无限隧道。
 */
export function buildCorridorFrame(
  scene: Phaser.Scene,
  width: number,
  height: number,
  options?: { showProps?: boolean },
): CorridorFrameResult {
  const showProps = options?.showProps ?? true;
  const container = scene.add.container(0, 0);
  const portal = scene.add.container(width / 2, height / 2);

  const hole = width * TUNNEL_INNER_RATIO;
  const holeHalf = hole / 2;
  const cx = width / 2;
  const cy = height / 2;
  const holeTop = cy - holeHalf;
  const floorTop = height * 0.4;
  const floorBot = height * 0.97;

  const bg = scene.add.graphics();
  bg.fillStyle(0x14141a, 1);
  bg.fillRect(0, 0, width, height);

  const floor = scene.add.graphics();
  floor.fillStyle(0x2a2830, 1);
  floor.beginPath();
  floor.moveTo(cx - width * 0.07, floorTop);
  floor.lineTo(cx + width * 0.07, floorTop);
  floor.lineTo(width, floorBot);
  floor.lineTo(0, floorBot);
  floor.closePath();
  floor.fillPath();

  floor.lineStyle(2, 0x3d3848, 0.85);
  for (let i = 0; i < 5; i++) {
    const t = i / 4;
    const y = Phaser.Math.Linear(floorTop, floorBot, t);
    const half = Phaser.Math.Linear(width * 0.07, width * 0.48, t);
    floor.lineBetween(cx - half, y, cx + half, y);
  }

  const walls = scene.add.graphics();
  walls.fillStyle(0x22222c, 1);
  walls.fillTriangle(0, 0, cx - holeHalf - 8, holeTop, 0, height);
  walls.fillTriangle(width, 0, cx + holeHalf + 8, holeTop, width, height);
  walls.fillRect(0, 0, cx - holeHalf - 8, holeTop);
  walls.fillRect(cx + holeHalf + 8, 0, width - (cx + holeHalf + 8), holeTop);

  const frame = scene.add.graphics();
  frame.lineStyle(3, 0x4a4558, 1);
  frame.strokeRect(cx - holeHalf, holeTop, hole, hole);
  frame.lineStyle(2, 0x2e2a38, 1);
  frame.strokeRect(cx - holeHalf + 4, holeTop + 4, hole - 8, hole - 8);

  if (showProps) {
    const chestY = height * 0.48;
    const chest = scene.add.rectangle(cx, chestY, width * 0.09, height * 0.055, 0x6b4a2a);
    chest.setStrokeStyle(2, 0x3d2818);
    const chicken = scene.add.ellipse(
      width * 0.7,
      height * 0.52,
      width * 0.12,
      height * 0.14,
      0xf5e6a8,
    );
    chicken.setStrokeStyle(2, 0xc9a227);
    container.add([bg, floor, walls, chest, chicken, portal, frame]);
  } else {
    container.add([bg, floor, walls, portal, frame]);
  }

  return { container, portal, width, height };
}

/** 最深处封口（避免无限递归时空洞） */
export function buildTunnelEndCap(
  scene: Phaser.Scene,
  width: number,
  height: number,
): Phaser.GameObjects.Container {
  const cap = scene.add.container(-width / 2, -height / 2);
  const g = scene.add.graphics();
  g.fillStyle(0x0a0a10, 1);
  g.fillRect(0, 0, width, height);
  g.fillStyle(0x1a1820, 1);
  g.fillRect(width * 0.35, height * 0.35, width * 0.3, height * 0.3);
  cap.add(g);
  return cap;
}
