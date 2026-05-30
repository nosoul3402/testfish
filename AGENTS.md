# AGENTS.md

## Cursor Cloud specific instructions

### What this repository is

`testfish` is a **partial source checkout** of **CatchFish** (FishX), a Cocos2d-x **2.1.5** mobile arcade fishing game (C++/Objective-C++/Java). The tree under `cocos2d-x-2.1.5/` contains game logic and a **truncated** engine slice—not a complete, runnable game project.

There is **no** `package.json`, Docker Compose, README, or platform project files (`proj.ios`, full `proj.android` with manifest/NDK, Linux target for CatchFish). **Game assets** (plist/png/audio under paths like `game/`, `Loading/`) are **not** in the repo.

### Services

| Component | Required for CatchFish E2E | In this repo |
|-----------|---------------------------|--------------|
| Backend / DB | No | N/A |
| Full Cocos2d-x 2.1.5 SDK | Yes | Partial only |
| Game assets | Yes | Missing |
| iOS (Xcode) or Android (NDK) toolchain | Yes (target platform) | Not configured |

### Dev environment (Linux VM)

System packages used in Cloud Agent setup:

- `build-essential`, `g++`, `clang`, `cmake`, `python3`, `default-jdk`
- OpenGL / X11: `libgl1-mesa-dev`, `libglew-dev`, `libfontconfig1-dev`, `libx11-dev`, `libxi-dev`, `libxrandr-dev`, `libcurl4-openssl-dev`, `libglfw3-dev`, `libxmu-dev`, `libglu1-mesa-dev`, `libzip-dev`, `libsqlite3-dev`

Optional: clone upstream engine (not vendored in repo):

```bash
git clone --depth 1 --branch cocos2d-x-2.1.5 https://github.com/cocos2d/cocos2d-x.git /tmp/cocos2d-x-full
```

Building **upstream** Cocos2d-x 2.1.5 on Ubuntu 24.04 with GCC 13 typically needs relaxed `-Werror` in `cocos2dx/proj.linux/cocos2dx.mk` and legacy **GLFW 2** headers (`GL/glfw.h`) for the Linux port—expect friction; iOS/Android are the historically supported targets.

### Commands in *this* repo

From repository root:

| Task | Command |
|------|---------|
| Smoke-test CatchFish save encoding | `make -C tools verify` |
| Clean smoke test binary | `make -C tools clean` |

There are **no** in-repo lint or unit-test targets. Full-game builds belong on a machine with Xcode or Android NDK plus the complete engine and assets.

### CatchFish billing / offline testing

For real device builds, set free/offline billing in `AppDelegate::setBillingModel()` and use `JNIHELPER_NUKNOW` in `GMFashion_Config.h` to avoid carrier/IAP SDKs (see source comments).

### Cloud Agent smoke test

`tools/dev_verify` compiles `DataBase64Himi` (used by `GMAccessData` for local saves) and checks encode/decode round-trip. This validates that the CatchFish C++ toolchain path works; it does **not** launch the game client.
