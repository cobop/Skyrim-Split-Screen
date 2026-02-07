# Changelog

All notable changes to **Skyrim Split‑Screen Launcher** will be documented in this file.

## [0.1.0] - 2026‑02‑07
### Added
- Project scaffolding with CMake build system.
- Core configuration handling (`Config.h/.cpp`) with JSON I/O using nlohmann/json.
- Stub `GameInstance` implementation that launches a dummy process and manages PID.
- `WindowManager` stub for window placement (prints intended command).
- Qt UI (`MainWindow`) with start/stop buttons, logging, and configuration loading.
- `Launcher` class orchestrating left/right instances.
- Comprehensive `README.md` with overview, features, build & install instructions, usage, and configuration example.
- GPL‑3.0 `LICENSE` file.
- `CONTRIBUTING.md` guidelines.
- Basic GoogleTest suite (`tests/test_config.cpp`).
- Flatpak manifest (`flatpak/com.example.SkyrimSplitScreen.yaml`).

### Changed
- Updated `GameInstance` to set Proton prefix environment variable and launch via `steam://run/` using a shell command.
- Added `stopAll` action to UI and integrated with `Launcher`.

### Fixed
- Various minor formatting and header comment updates to include SPDX license identifiers.

## [Unreleased]
- Implement real window positioning in `WindowManager`.
- Expand test suite for `GameInstance` and `WindowManager`.
- Add screenshots/examples to `README.md`.
- Create release tags and publish to GitHub/Flathub.
