# 技能图标自动载入

将图标放在本目录下，与 `DefaultSkillBar.ts` 里 `iconResourcePath` 对应：

| 路径 | 技能 |
|------|------|
| `skills/attack/spriteFrame` | 普攻 |
| `skills/block/spriteFrame` | 格挡 |
| `skills/dodge/spriteFrame` | 闪避 |

也可在编辑器里给 `SkillCard` 组件直接拖 **SpriteFrame**，优先于路径加载。

未放图时显示圆角方框 + 文字（如「空手」「格挡」）。
