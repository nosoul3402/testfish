import { SkillAction } from '../ui/SkillTypes';

/** 初期技能栏配置（文字占位；有图后由 SkillCard 自动载入） */
export interface SkillBarEntry {
  skillId: string;
  label: string;
  action: SkillAction;
  /** resources 下路径，如 skills/block/spriteFrame */
  iconResourcePath?: string;
}

export const DefaultSkillBarLayout: SkillBarEntry[] = [
  { skillId: 'empty_hand', label: '空手', action: SkillAction.WeaponDisplay },
  { skillId: 'attack', label: '普攻', action: SkillAction.NormalAttack, iconResourcePath: 'skills/attack/spriteFrame' },
  { skillId: 'block', label: '格挡', action: SkillAction.Block, iconResourcePath: 'skills/block/spriteFrame' },
  { skillId: 'dodge', label: '闪避', action: SkillAction.Dodge, iconResourcePath: 'skills/dodge/spriteFrame' },
];
