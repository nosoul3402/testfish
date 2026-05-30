/** 全局事件名（可在任意脚本中 emit / on） */
export const GameEvents = {
  /** 完成一次“前进”缩放 */
  TUNNEL_STEP_DONE: 'tunnel-step-done',
  /** 切换到新场景帧前（可改 UI） */
  SCENE_FRAME_WILL_CHANGE: 'scene-frame-will-change',
  /** 场景帧已切换 */
  SCENE_FRAME_CHANGED: 'scene-frame-changed',
  /** 进门过渡开始 */
  DOOR_ENTER_START: 'door-enter-start',
  /** 进门过渡结束，已加载下一场景 */
  DOOR_ENTER_DONE: 'door-enter-done',
} as const;
