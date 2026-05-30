import { Enum } from 'cc';

export enum MonsterState {
  Resting = 0,
  Suspicious = 1,
  Alert = 2,
  Approaching = 3,
  Combat = 4,
  Casting = 5,
  Attacking = 6,
  Dead = 7,
}

export enum AttackKind {
  Melee = 0,
  Ranged = 1,
  Skill = 2,
}

/** 可打断读条的技能标签（后期眩晕、沉默等） */
export enum SkillTag {
  Damage = 1,
  Interrupt = 2,
  Stun = 4,
}

Enum(MonsterState);
Enum(AttackKind);
Enum(SkillTag);

export interface MonsterAttackConfig {
  id: string;
  kind: AttackKind;
  damage: number;
  /** 技能读条秒数；普攻/远程可为前摇 */
  castTime: number;
  cooldown: number;
  weight: number;
}

export interface MonsterConfigData {
  id: string;
  displayName: string;
  maxHp: number;
  /** 休息态权重（1 - earlyAlert） */
  restChance: number;
  attacks: MonsterAttackConfig[];
}
