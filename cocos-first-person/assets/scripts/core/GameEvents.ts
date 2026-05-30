/** 全局事件名（可在任意脚本中 emit / on） */
export const GameEvents = {
  TUNNEL_STEP_DONE: 'tunnel-step-done',
  SCENE_FRAME_WILL_CHANGE: 'scene-frame-will-change',
  SCENE_FRAME_CHANGED: 'scene-frame-changed',
  DOOR_ENTER_START: 'door-enter-start',
  DOOR_ENTER_DONE: 'door-enter-done',

  /** 探索态：可前进 */
  EXPLORING_ENABLED: 'exploring-enabled',
  EXPLORING_DISABLED: 'exploring-disabled',

  ENCOUNTER_START: 'encounter-start',
  ENCOUNTER_END: 'encounter-end',
  COMBAT_START: 'combat-start',
  COMBAT_END: 'combat-end',
  MONSTER_STATE_CHANGED: 'monster-state-changed',
  CAST_START: 'cast-start',
  CAST_RELEASE: 'cast-release',
  CAST_INTERRUPTED: 'cast-interrupted',

  PLAYER_HP_CHANGED: 'player-hp-changed',
  /** 杀戮尖塔式整局重来 */
  RUN_RESTART: 'run-restart',
} as const;
