import { SkillAction } from '../ui/SkillTypes';

/**
 * 玩家单次出手配置。
 * castTimeSec = 0 表示半即时下「立刻出手」；后期可改为 0.3~1.5s 读条。
 */
export interface PlayerActionDef {
  action: SkillAction;
  /** 施法/前摇秒数，0 = 按下即生效 */
  castTimeSec: number;
  damage?: number;
  /** 施法过程中是否允许再次按键（一般 false） */
  allowRepressDuringCast?: boolean;
}

/** 默认出手时间（可在编辑器用 PlayerCombat 覆盖） */
export const DefaultPlayerActions: Record<string, PlayerActionDef> = {
  attack: { action: SkillAction.NormalAttack, castTimeSec: 0, damage: 10 },
  block: { action: SkillAction.Block, castTimeSec: 0 },
  dodge: { action: SkillAction.Dodge, castTimeSec: 0 },
  weapon: { action: SkillAction.WeaponAttack, castTimeSec: 0, damage: 12 },
};
