# AGENTS.md

## Cursor Cloud specific instructions

### Primary project

**`cocos-first-person/`** — Cocos Creator 3.8+ scripts for WeChat Mini Game (no npm dev server in-repo). Open or copy into a Creator project locally; see `cocos-first-person/docs/EDITOR_SETUP.md`.

### Optional web prototype

**`first-person-2d/`** — Phaser tunnel demo:

```bash
cd first-person-2d && npm install && npm run dev
```

Port **5173**.

### VM update script

```text
cd first-person-2d
npm install
```

(`cocos-first-person` has no Node deps until Creator generates them.)

### WeChat publish

Done in Creator: Build → WeChat Mini Game. Template under `cocos-first-person/build-templates/wechatgame/`.
