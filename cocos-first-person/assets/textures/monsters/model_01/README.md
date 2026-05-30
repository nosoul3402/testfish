# 怪物模型 1（model_01）

请将**派对猫**图片保存为本目录下的：

```
model_01.png
```

## 在 Cocos Creator 中

1. 把 `model_01.png` 拖进此文件夹（或资源管理器 `assets/textures/monsters/model_01/`）。
2. 选中图片 → 属性：**Sprite Frame** 类型，勾选透明通道（若需抠图请在 PS 等工具去底）。
3. 打开 **Game** 场景 → `GameLogic` → **MonsterModelRegistry**：
   - 在 `models` 列表中找到 `model_01`
   - 将生成的 **SpriteFrame** 拖到 `spriteFrame` 槽位。

也可放到 `assets/resources/monsters/model_01.png`，由脚本按路径 `monsters/model_01/spriteFrame` 自动加载（无需拖槽）。

## 战斗表现

- 遭遇时从注册表**随机**抽取已配置模型（目前含 model_01）。
- 显示在 **MonsterSlot 正中**，受击/攻击为**单图抖动**（`MonsterView`）。
