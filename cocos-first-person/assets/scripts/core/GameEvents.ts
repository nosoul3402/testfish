/** 全局事件名（可在任意脚本中 emit / on） */
export const GameEvents = {
  TUNNEL_STEP_DONE: 'tunnel-step-done',
  SCENE_FRAME_WILL_CHANGE: 'scene-frame-will-change',
  SCENE_FRAME_CHANGED: 'scene-frame-changed',
  DOOR_ENTER_START: 'door-enter-start',
  DOOR_ENTER_END: 'door-enter-end',

  EXPLORING_ENABLED: 'exploring-enabled',
  EXPLORING_DISABLED: 'exploring-disabled',

  ENCOUNTER_START: 'encounter-start',
  ENCOUNTER_END: 'encounter-end',
  COMBAT_START: 'combat-start',
  COMBAT_END: 'combat-end',
  MONSTER_STATE_CHANGED: 'monster-state-changed',
  MONSTER_DEFEATED: 'monster-defeated',
  CAST_START: 'cast-start',
  CAST_RELEASE: 'cast-release',
  CAST_INTERRUPTED: 'cast-interrupted',

  PLAYER_HP_CHANGED: 'player-hp-changed',
  PLAYER_ACTION_START: 'player-action-start',
  PLAYER_ACTION_RELEASE: 'player-action-release',
  RUN_RESTART: 'run-restart',

  /** 隧道尽头城镇大门已显示，可交互 */
  GATE_REVEALED: 'gate-revealed',
  GATE_ENTER_REQUEST: 'gate-enter-request',
  ENTER_TOWN: 'enter-town',
} as const;
