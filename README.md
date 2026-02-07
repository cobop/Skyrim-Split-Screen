# Skyrim Split‑Screen Launcher

![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)

## Overview
A C++ Qt‑based launcher that starts **two** Skyrim (Special Edition) instances via **Proton**, automatically places each window on a separate monitor, and optionally connects them to a **SkyrimTogether** server. The application is packaged as a **Flatpak** for universal Linux deployment, making split‑screen co‑op on a single machine easy and reproducible.

## Features
- Launch two Skyrim instances side‑by‑side using Proton.
- Automatic window placement on user‑specified monitors (X11 and Wayland fallback).
- Simple Qt GUI with start/stop buttons, status indicators, and a configuration editor.
- JSON‑based configuration file for easy tweaking.
- Optional integration with a SkyrimTogether server.
- Fully Open‑Source (GPL‑3.0) and distributed via Flatpak.

## Prerequisites
- **Linux** distribution with Flatpak support.
- **Qt 6 (Widgets)** development libraries.
- **Proton** (installed via Steam) – the launcher only invokes it.
- **CMake ≥ 3.16**.
- Optional: `xrandr`/`wmctrl` (X11) or a Wayland compositor that supports window positioning.

## Build & Install

```bash
# Clone the repository
git clone https://github.com/yourname/SkyrimSplitScreen.git
cd SkyrimSplitScreen

# Create a build directory
mkdir build && cd build

# Configure the project
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
make -j$(nproc)

# Run the launcher
./SkyrimSplitScreen
```

### Flatpak

```bash
flatpak-builder --user --install --force-clean build-dir com.example.SkyrimSplitScreen.yaml
flatpak run com.example.SkyrimSplitScreen
```

## Usage
1. Launch the application.
2. Edit the configuration (Steam App ID, Proton prefix, monitor indices, etc.) or use the defaults.
3. Click **Start Left** and **Start Right** to launch the two instances.
4. (Optional) Enable the **SkyrimTogether** toggle to join a server automatically.

## Configuration File
The launcher reads `config.json` in the working directory. Example:

```json
{
  "steam_app_id": "228200",
  "proton_prefix": "/home/jane/.steam/steam/steamapps/compatdata/228200/pfx",
  "skyrim_together_url": "https://skyrim.together.example",
  "launch_args": "",
  "placement": "CUSTOM",
  "monitor_left": 0,
  "monitor_right": 1
}
```

## Contributing
- Fork the repository and create a feature branch.
- Follow the existing code style (C++17, Qt‑style guidelines).
- Add unit tests under `tests/`.
- Run `clang-format` before committing.
- Submit a pull request with a clear description of changes.

## License
This project is released under the **GNU General Public License v3.0**. See the `LICENSE` file for details.

## Acknowledgements
- **Qt** – cross‑platform GUI framework.
- **Proton** – compatibility layer for Windows games on Linux.
- **SkyrimTogether** – community server for multiplayer Skyrim.

---

*Happy split‑screen gaming!*
