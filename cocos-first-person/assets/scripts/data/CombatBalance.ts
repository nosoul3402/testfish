/** 已定稿战斗数值（见 docs/COMBAT_PLAN.md） */
export const CombatBalance = {
  /** 每 N 次前进触发遭遇 */
  stepsPerEncounter: 3,
  /** 偷袭：+100% 伤害（总伤害 = 基础 × 2） */
  sneakDamageMultiplier: 2,
  /** 遭遇时怪物处于「已发现玩家」的概率 */
  earlyAlertChance: 0.2,
  /** 普攻读条不可被普攻打断；仅 INTERRUPT 类技能可打断 */
  normalAttackInterruptsCast: false,
  /** 玩家默认 HP */
  playerMaxHp: 100,
  /** 杀戮尖塔式死亡后加载的场景 */
  runStartScene: 'Game',
  /** 格挡时受到伤害倍率 */
  blockDamageRatio: 0.25,
  /** 闪避持续秒数（吃下一段伤害前有效） */
  dodgeIFrameSec: 1.2,
} as const;
