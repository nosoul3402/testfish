import { Enum } from 'cc';

/** 底部技能卡对应的行为 */
export enum SkillAction {
  NormalAttack = 0,
  Block = 1,
  Dodge = 2,
  WeaponAttack = 3,
  /** 仅展示武器/空手状态，不可点 */
  WeaponDisplay = 4,
}

Enum(SkillAction);
