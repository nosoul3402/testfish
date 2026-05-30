import { SkillAction } from '../ui/SkillTypes';

/** 初期技能栏配置（文字占位；有图后由 SkillCard 自动载入） */
export interface SkillBarEntry {
  skillId: string;
  label: string;
  action: SkillAction;
  iconResourcePath?: string;
  /** 玩家出手读条（秒）；0 = 即时，与半即时「怪读条时我可插招」并存 */
  castTimeSec?: number;
  damage?: number;
}

export const DefaultSkillBarLayout: SkillBarEntry[] = [
  { skillId: 'empty_hand', label: '空手', action: SkillAction.WeaponDisplay },
  {
    skillId: 'attack',
    label: '普攻',
    action: SkillAction.NormalAttack,
    iconResourcePath: 'skills/attack/spriteFrame',
    castTimeSec: 0,
    damage: 10,
  },
  {
    skillId: 'block',
    label: '格挡',
    action: SkillAction.Block,
    castTimeSec: 0,
  },
  {
    skillId: 'dodge',
    label: '闪避',
    action: SkillAction.Dodge,
    castTimeSec: 0,
  },
];
