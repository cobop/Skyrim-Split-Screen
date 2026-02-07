# Implementation Plan

[Overview]
Create a C++ Qt/GTK launcher that starts two Skyrim instances via Proton, positions each on a separate screen, connects them to a SkyrimTogether server, and distributes the launcher as a Flatpak for universal Linux deployment.

This project enables split‑screen co‑op on a single Linux machine by automating the launch and window management of two Skyrim instances. It abstracts the complexities of Proton invocation, monitor placement, and server connectivity behind a simple graphical interface, making the experience accessible to users without manual configuration.

[Types]  
Define core data structures for configuration, screen placement, and game instance metadata.

```cpp
enum class ScreenPlacement { LEFT, RIGHT, CUSTOM };

struct Config {
    std::string steam_app_id;          // e.g., "228200" for Skyrim Special Edition
    std::string proton_prefix;         // Path to Proton prefix
    std::string skyrim_together_url;   // Server URL
    std::string launch_args;           // Additional launch arguments
    ScreenPlacement placement;          // Enum: LEFT, RIGHT, CUSTOM
    int monitor_left;                  // X11 monitor index for first instance
    int monitor_right;                 // X11 monitor index for second instance
};
```

[Files]
Core source files, build configuration, resources, and packaging manifest.

| Path | Purpose |
|------|---------|
| `CMakeLists.txt` | Build configuration (C++17, Qt6, linking) |
| `src/main.cpp` | Application entry point, Qt event loop |
| `src/Launcher.cpp` / `src/Launcher.h` | Core logic for spawning Skyrim via Proton and managing processes |
| `src/Config.cpp` / `src/Config.h` | Load/save JSON configuration (using nlohmann/json) |
| `src/GameInstance.cpp` / `src/GameInstance.h` | Wrapper around a single Skyrim process (PID, window ID) |
| `src/WindowManager.cpp` / `src/WindowManager.h` | Position windows on chosen monitors (X11/Wayland fallback) |
| `src/UI/MainWindow.cpp` / `src/UI/MainWindow.h` | Simple Qt GUI (two start buttons, status indicators, config editor) |
| `flatpak/com.example.SkyrimSplitScreen.yaml` | Flatpak manifest (runtime: org.kde.Platform, SDK: org.kde.Sdk) |
| `resources/icons/` | Application icons |
| `tests/` | GoogleTest unit tests for Config, Launcher, WindowManager |

[Functions]
Key procedural units that perform launching, window handling, and server connection.

- `bool launchSkyrim(const Config&, ScreenPlacement side)` – builds `steam://run/<appid>` URL, invokes Proton with proper environment variables. Returns success flag.
- `pid_t getWindowPid(WindowId)` – retrieve PID of a window to associate with a `GameInstance`.
- `void setWindowPosition(WindowId, int monitorIndex)` – uses `xrandr`/`wmctrl` or Wayland compositor APIs.
- `void connectToSkyrimTogether(const Config&)` – optional stub to launch a helper that joins the specified server.
- `Config loadConfig(const std::string& path)` / `void saveConfig(const Config&, const std::string& path)` – JSON I/O.

[Classes]
Object‑oriented components that encapsulate functionality.

- **Launcher** – orchestrates two `GameInstance`s, handles start/stop, error reporting.
- **GameInstance** – stores PID, window ID, monitor assignment; provides `terminate()` method.
- **ConfigManager** – thin wrapper around file I/O; notifies UI on changes.
- **WindowManager** – abstracts X11/Wayland specifics; provides `placeWindow(GameInstance&, ScreenPlacement)`.
- **MainWindow (Qt)** – UI elements: start buttons, status panels, config editor, log view.

[Dependencies]
External libraries and runtimes required for building and running the launcher.

- **Qt6 (Widgets)** – UI framework.  
- **nlohmann/json** – JSON parsing for configuration.  
- **GoogleTest** – unit testing.  
- **Flatpak Builder** – packaging.  
- **X11/Xrandr** (or **wlroots** for Wayland) – window manipulation.  
- **Proton (Steam)** – already installed by the user; launcher only invokes it.

[Testing]
Approach to verify correctness at unit, integration, and UI levels.

- **Unit Tests** – Config serialization, command line construction, WindowManager calculations (mocked X11).  
- **Integration Tests** – launch a dummy “sleep” process and verify window placement logic.  
- **UI Tests** – basic sanity checks using Qt Test (button enabled/disabled states).  
- **Flatpak Validation** – `flatpak-builder --run` to ensure the app launches inside the sandbox.

[Implementation Order]
Logical sequence to minimise conflicts and ensure a working prototype early.

1. Initialise git repository and CMake project structure.  
2. Add `Config` type and JSON load/save implementation.  
3. Implement `Launcher` class with stub `launchSkyrim` that only prints the command.  
4. Build minimal Qt `MainWindow` that calls the stub launcher.  
5. Implement `GameInstance` and integrate real Proton launch using `steam://run/<appid>`.  
6. Add `WindowManager` with X11 positioning; provide fallback for Wayland.  
7. Wire up two concurrent instances, ensure each window is placed on the correct monitor.  
8. Add optional `connectToSkyrimTogether` integration (invoke external helper).  
9. Write unit and integration tests; achieve >80% coverage.  
10. Create Flatpak manifest, test with `flatpak-builder`, and publish to Flathub.  
11. Final documentation, user guide, and release tagging.
