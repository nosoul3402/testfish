# AGENTS.md

## Cursor Cloud specific instructions

### Repository layout

- All game code lives in **`first-person-2d/`** (Vite + TypeScript + Phaser 3).
- Legacy Cocos2d-x / CatchFish sources were removed.

### Services

| Service | Required | Command |
|---------|----------|---------|
| Vite dev server | Yes (local playtest) | `npm run dev` in `first-person-2d/` |
| Backend | No | — |

### Commands (from `first-person-2d/`)

| Task | Command |
|------|---------|
| Install deps | `npm install` |
| Dev server | `npm run dev` (port **5173**, `host: true`) |
| Production build | `npm run build` |
| Preview build | `npm run preview` |

### VM update script

Run `npm install` inside `first-person-2d/` on startup (see SetupVmEnvironment).

### Notes

- Portrait layout **390×844**, scaled with `Phaser.Scale.FIT`.
- Main scene: `src/scenes/GameScene.ts` — corridor, hands, HUD, inventory grid (placeholder graphics).
