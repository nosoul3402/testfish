# Cocos Creator · 2D 第一人称 · 微信小程序

用 **Cocos Creator 3.8+** 做竖屏第一人称走廊：中心嵌套图放大 = 前进；透明 PNG 左右/上方；多场景帧序列；点击左右门放大 + 黑场切场景。

> 用 **Cocos Creator 3.8+** 直接打开本目录（含 `project.json`）。脚本支持 **TypeScript**（`assets/scripts/`）与 **JavaScript**（`assets/scripts-js/`，二选一）。

**快速说明**：[docs/QUICKSTART.md](./docs/QUICKSTART.md) · **搭场景**：[docs/EDITOR_SETUP.md](./docs/EDITOR_SETUP.md) · **战斗**：[docs/COMBAT_PLAN.md](./docs/COMBAT_PLAN.md) · **关卡/城镇策划**：[docs/GAME_FLOW_AND_EDITING.md](./docs/GAME_FLOW_AND_EDITING.md)

## 核心思路（与你描述一致）

| 做法 | 说明 |
|------|------|
| **只放大内层图** | 子图锚点在远处洞口中心，初始 `scale ≈ 0.36`，前进时 tween 到 `1` |
| **可选上移** | `alsoMoveUp` + `moveUpDistance`，加强纵深感 |
| **调速度** | `TunnelForwardController.zoomDuration`（秒） |
| **透明边** | 美术 PNG 左/右/上透明，见 `assets/textures/README.md` |
| **多场景** | `TunnelSceneSequence.frames[]`，每步或每 N 步换下一张 |
| **无限前进** | `loopSequence = true` |
| **进门** | `DoorPortal`：向门锚点放大 → `FadeOverlay` → `loadScene` |

## 脚本一览

| 脚本 | 作用 |
|------|------|
| `TunnelForwardController` | 中心放大（+ 可选上移） |
| `TunnelSceneSequence` | 多帧贴图轮换 |
| `TunnelTapArea` | 点击 / 空格 / W 前进 |
| `DoorPortal` | 左右门：聚焦放大 + 黑场 + 切场景 |
| `FadeOverlay` | 全屏淡入淡出 |
| `SceneFlowController` | 序列最后一帧加载下一大关 |

## 发布微信小程序

1. Creator：**项目 → 构建发布 → 微信小游戏**，填 AppID。  
2. 构建产物用 **微信开发者工具** 打开 `build/wechatgame`（或你的构建目录）。  
3. 可改 `build-templates/wechatgame/project.config.json` 模板（会合并进构建结果）。

官方文档：[发布到微信小游戏](https://docs.cocos.com/creator/3.8/manual/zh/editor/publish/publish-wechatgame.html)

## 与 `first-person-2d/` 的关系

- `first-person-2d/`：Phaser 网页原型，验证隧道递归思路。  
- **`cocos-first-person/`**：正式方向，面向小程序 + 你熟悉的 Creator 工作流。
