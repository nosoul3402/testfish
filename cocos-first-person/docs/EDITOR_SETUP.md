# Cocos Creator 编辑器搭场景（推荐 3.8）

## 1. 创建项目

1. 打开 Cocos Creator → **新建** → 空项目（3D/2D 均可，脚本为 2D UI）。
2. 将本仓库 `cocos-first-person/assets/scripts` 复制到项目的 `assets/scripts`。
3. 将 `build-templates` 复制到项目根目录（可选，用于微信模板）。

## 2. 节点层级（竖屏 750×1334 示例）

```
Canvas
├── TunnelRoot                    # 隧道视野区（上 58% 屏高）
│   ├── Frame (Sprite)            # 外层走廊 PNG，透明左右上
│   └── Inner (Sprite)            # 内层同图或下一帧；对准洞口中心
├── Hands                         # 双手（不参与缩放）
├── HUD                           # 金币、进度条
├── Inventory                     # 底部装备栏
├── FadeOverlay (Sprite 纯黑 + UIOpacity + FadeOverlay.ts)
├── MonsterSlot                   # 走廊正中；单怪/战士用
│   ├── Body (Sprite 单图)
│   ├── ZzzRoot (+ Label "Z z z")
│   └── CastBar (+ CastBarUI + Fill Sprite)
├── GameLogic (空节点 = eventBus)
│   ├── TunnelForwardController
│   ├── TunnelSceneSequence
│   ├── TunnelTapArea
│   ├── TunnelCombatGate
│   ├── EncounterScheduler
│   ├── CombatDirector
│   ├── PlayerCombat
│   └── RunRestartController
└── Doors
    ├── DoorLeft  (+ DoorPortal, FocusAnchor 子节点)
    └── DoorRight (+ DoorPortal)
```

## 3. 组件绑定

### Frame / Inner

- **Frame**：`Sprite`，SpriteFrame = 当前走廊图。  
- **Inner**：`Sprite`，位置拖到 **洞口中心**（与美术 `holeCenter` 一致），锚点 **(0.5, 0.5)**。  
- 初始 **Inner.scale = (0.36, 0.36, 1)**（与 `innerScaleStart` 一致）。

### TunnelForwardController

| 属性 | 拖入 |
|------|------|
| innerTunnel | Inner 节点 |
| innerScaleStart | 0.36 |
| zoomDuration | 0.52（越小越快） |
| alsoMoveUp | 按需勾选 |
| moveUpDistance | 30~60 |
| eventBus | GameLogic 节点 |

### TunnelSceneSequence

| 属性 | 说明 |
|------|------|
| frames | 拖入多张 SpriteFrame（走廊 A/B/C…） |
| outerFrame | Frame 的 Sprite |
| innerFrame | Inner 的 Sprite |
| tunnel | TunnelForwardController |
| loopSequence | 无限前进勾 true |
| stepsPerFrame | 1 = 每走一步换图 |

### 点击前进

- 在 `TunnelRoot` 上盖一层透明 **UITransform + Button**（或仅 UITransform + `TunnelTapArea`）。  
- `TunnelTapArea.tunnel` → TunnelForwardController。

### 左右门

1. `DoorLeft` 下建子节点 `FocusAnchor`，放在门洞中心。  
2. `DoorPortal`：  
   - zoomTarget → Inner（或整个 TunnelRoot）  
   - focusAnchor → FocusAnchor  
   - fadeOverlay → FadeOverlay 节点  
   - nextSceneName → Build Settings 里的场景名  

## 4. 微信小程序

1. **项目设置** → 裁剪功能：按需关闭 3D、物理等以减小包体。  
2. **构建发布** → 微信小游戏 → 竖屏 portrait。  
3. 微信开发者工具导入构建目录，预览真机。

## 5. 调参建议

- 先 **只开放大、不上移**，调 `zoomDuration` 到手感合适。  
- 再开 `alsoMoveUp`，避免位移过大导致穿帮。  
- 多场景用 3~5 张差异明显的 PNG，最后一张接 `SceneFlowController.nextLevelScene`。
