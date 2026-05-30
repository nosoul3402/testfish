# 第一人称 2D 游戏（微信小程序 · Cocos Creator）

## 推荐工程：`cocos-first-person/`

面向 **微信小游戏**，使用 **Cocos Creator 3.8+**：

- 中心子图 **放大**（锚点在远处洞口）= 前进；`zoomDuration` 控制速度  
- 美术 PNG **左右/上方透明**  
- **多场景帧** 轮换 / 循环，实现无限前进  
- **左右门**：向门点放大 → 黑场 → `loadScene`

```text
cocos-first-person/
├── assets/scripts/tunnel/   # TunnelForwardController、DoorPortal 等
├── assets/textures/README.md
├── docs/EDITOR_SETUP.md     # 编辑器节点与组件绑定
└── build-templates/wechatgame/
```

请阅读 [cocos-first-person/README.md](./cocos-first-person/README.md) 与 [docs/EDITOR_SETUP.md](./cocos-first-person/docs/EDITOR_SETUP.md)。

## 网页原型（可选）

[first-person-2d/](./first-person-2d/)：Phaser 3 递归隧道 demo，用于快速验证透视感，**非小程序发布目标**。

```bash
cd first-person-2d && npm install && npm run dev
```
