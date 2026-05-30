import { Enum } from 'cc';

/** 前进动画模式 */
export enum TunnelForwardMode {
  /** 仅放大内层图（锚点在洞口中心，推荐） */
  ScaleOnly = 0,
  /** 放大 + 向上移动 */
  ScaleAndMoveUp = 1,
}

Enum(TunnelForwardMode);
