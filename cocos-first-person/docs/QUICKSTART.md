# 5 分钟上手（微信小程序 + Cocos Creator）

## 你要的效果 ↔ 怎么做

| 目标 | 做法 |
|------|------|
| 往前走 | `Inner` 对准洞口中心，**只放大** `scale: 0.36 → 1` |
| 走快点/慢点 | 调 `zoomDuration`（秒）或 `forwardSpeed`（1~10） |
| 想带上移 | `forwardMode` → **ScaleAndMoveUp** |
| 左右上透明 | 走廊用 **PNG 透明**，见 `assets/textures/README.md` |
| 多张场景 | `TunnelSceneSequence.frames` 拖 SpriteFrame |
| 无限前进 | `loopSequence = true` |
| 最后一张换大关 | `loopSequence = false` + `SceneFlowController.nextLevelScene` |
| 点左/右门 | `DoorPortal`：向门放大 → 黑屏 → `loadScene` |

## 打开工程

1. **Cocos Creator 3.8+** → 打开项目 → 选目录 `cocos-first-person/`（含 `project.json`）。
2. 若提示升级/生成 meta，允许即可。

## 最小节点（竖屏）

```
Canvas
└── TunnelRoot
    ├── Frame   (Sprite 外层 PNG)
    └── Inner   (Sprite 内层，位置=洞口中心，scale 0.36)
```

`GameLogic` 空节点挂：

- `TunnelForwardController`（TypeScript）**或** `TunnelForwardControllerJs`（JavaScript）
- `TunnelTapArea`（透明点击区）
- 按需：`TunnelSceneSequence`、`DoorPortal`、`FadeOverlay`

详细层级见 [EDITOR_SETUP.md](./EDITOR_SETUP.md)。

## TypeScript 还是 JavaScript？

| 目录 | 说明 |
|------|------|
| `assets/scripts/` | **TypeScript（推荐）** |
| `assets/scripts-js/` | **JavaScript**，逻辑相同，类名带 `Js` 后缀，勿与 TS 重复挂在同一节点 |

构建小程序时 Creator 都会编译为 JS。

## 发布微信

菜单 **项目 → 构建发布 → 微信小游戏** → 填 AppID → 用微信开发者工具打开 `build/wechatgame`。
