# 美术资源规范（隧道第一人称）

## 单帧走廊 PNG

- **尺寸**：建议 750×1334 或 1080×1920（竖屏小程序）。
- **透明区域**：左、右、上可透明，只保留墙/地板/门框实体像素。
- **中心洞**：正方形镂空（或纯色 `#00000000`），洞心坐标记为 **焦点** `holeCenter`。
- **锚点**：
  - 外层 `Frame`：锚点 (0.5, 0.5)，节点在屏幕中心。
  - 内层 `Inner`：锚点 (0.5, 0.5)，**位置 = 父节点坐标系下的洞口中心**。

## 前进效果（无需多层递归）

1. `Inner` 初始 `scale = 0.36`（与洞口占宽比例一致）。
2. 前进：`scale → 1`，可选 `position.y += 40`。
3. 结束：重置 `scale/position`，换下一帧贴图（`TunnelSceneSequence`）。

仅调 **`zoomDuration`** 即可控制“走路速度”。

## 多场景

- `frames[0..n]`：走廊 A → 走廊 B → … → 尽头。
- `loopSequence = true`：无限循环同序列。
- 最后一张换完后 `SceneFlowController` 可 `loadScene` 到下一大关。

## 左右门

- 在 Frame 上标出门点击区，子节点 `FocusAnchor` 放在门中心。
- `DoorPortal`：向锚点放大 + 黑场 + `loadScene`。
