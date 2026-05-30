# 双手摆动 + 底部技能卡

## 1. 双手（参考图）

### 节点

```
Canvas
├── LeftHand   (Sprite 左手图)
└── RightHand  (Sprite 右手图)
```

挂 **`HandSwayController`**：

| 属性 | 说明 |
|------|------|
| leftHand / rightHand | 左右手节点 |
| exploreSwingAngle | 前进时摆动角度（默认 8°） |
| exploreSwingY | 上下位移（默认 12） |
| exploreCycleSec | 循环周期 |

- **探索/前进**：双手持续左右交替摆动；每次 `TUNNEL_STEP_DONE` 额外甩一下。  
- **战斗**：摆动减弱（`combatSwingAngle`）。

挂 **`HandAttackAnimator`**（可与左手同父或挂 GameLogic）：

| 属性 | 说明 |
|------|------|
| leftHand / rightHand | 同上 |
| punchForward | 普攻前探距离 |

普攻时 **`CombatSkillBar`** 会调用 `playAttackSwing()`。

---

## 2. 底部技能栏（遇怪显示）

### 节点

```
Canvas
└── CombatSkillBar (底对齐，Widget 贴底)
    └── BarRoot (Layout 横向)
        └── SkillCard × 4（或用 Prefab 生成）
```

挂 **`CombatSkillBar`**：

| 属性 | 绑定 |
|------|------|
| barRoot | BarRoot |
| cardPrefab | 可选；SkillCard 预制体 |
| player | PlayerCombat |
| handAttack | HandAttackAnimator |
| eventBus | GameLogic |

### SkillCard 预制体结构

```
SkillCard (UITransform 72×72)
├── Background (Graphics + SkillCard.background)
├── Icon (Sprite + SkillCard.iconSprite)  # 有图时显示
└── Label (Label + SkillCard.label)       # 无图时显示文字
```

`SkillCard` 组件：圆角底图在 `onLoad` 用 Graphics 绘制。

### 初期四格

| 卡 | 文字 | 行为 |
|----|------|------|
| 空手 | 空手 | 仅展示（WeaponDisplay） |
| 普攻 | 普攻 | normalAttack + 挥手 |
| 格挡 | 格挡 | 下次受伤 ×0.25 |
| 闪避 | 闪避 | 约 1.2s 内免疫一次伤害 |

配置代码：`assets/scripts/data/DefaultSkillBar.ts`。

### 后期换图

1. **编辑器**：SkillCard 上拖 `iconFrame`；或  
2. **resources**：放 `assets/resources/skills/attack.png` 等，路径见 `resources/skills/README.md`。

有图自动隐藏文字，无图显示圆角+文字。

---

## 3. 与战斗流程

- `COMBAT_START` → `CombatSkillBar` 显示  
- `COMBAT_END` → 隐藏  
- 探索时仅双手摆动，不显示技能栏  

---

## 4. 半即时与玩家读条

- 怪物准备攻击（读条）时，你仍可点底部技能卡，只要 **`PlayerCombat.canActNow`**。  
- 在 `DefaultSkillBar.ts` 或 `PlayerCombat.normalAttackCastTime` 设置 **`castTimeSec`**：  
  - `0`：即时出手（初期普攻）  
  - `>0`：玩家脚底/技能旁 **PlayerCastBarUI** 显示读条，结束后再结算伤害/格挡/闪避。  
- 怪读条与玩家读条**同时进行**，互不暂停。

## 5. 可选：武器攻击

获得武器后：

1. 在 `DefaultSkillBarLayout` 把「空手」改为武器名，或增加 `WeaponAttack` 卡。  
2. `HandAttackAnimator` 可换武器 Sprite 子节点。  
3. `action: SkillAction.WeaponAttack` 与普攻共用伤害，后期单独数值。
