import { AttackKind, MonsterConfigData } from '../combat/CombatTypes';

const defaultAttacks = [
  {
    id: 'melee',
    kind: AttackKind.Melee,
    damage: 8,
    castTime: 0.35,
    cooldown: 2.2,
    weight: 5,
  },
  {
    id: 'spit',
    kind: AttackKind.Ranged,
    damage: 6,
    castTime: 0.5,
    cooldown: 3,
    weight: 3,
  },
  {
    id: 'burst',
    kind: AttackKind.Skill,
    damage: 14,
    castTime: 1.6,
    cooldown: 5,
    weight: 2,
  },
] as const;

/** 史莱姆（占位） */
export const DefaultSlime: MonsterConfigData = {
  id: 'slime',
  displayName: '史莱姆',
  maxHp: 40,
  restChance: 0.8,
  attacks: [...defaultAttacks],
};

/** 怪物模型 1：派对猫 */
export const Model01PartyCat: MonsterConfigData = {
  id: 'model_01',
  displayName: '派对猫',
  maxHp: 45,
  restChance: 0.8,
  attacks: [...defaultAttacks],
};

export const MonsterConfigById: Record<string, MonsterConfigData> = {
  slime: DefaultSlime,
  model_01: Model01PartyCat,
};
