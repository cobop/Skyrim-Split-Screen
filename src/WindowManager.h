#pragma once
#include <string>
#include "GameInstance.h"
#include "Config.h"

/*
 * SPDX-FileCopyrightText: 2026 Jane Doe
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

class WindowManager {
public:
    WindowManager() = default;
    ~WindowManager() = default;

    /** Position the window of a given GameInstance on the monitor specified in the Config.
     *  Returns true on success, false otherwise.
     */
    bool placeWindow(const GameInstance& instance, const Config& config, ScreenPlacement side);

private:
    /** Helper that runs a system command to move a window identified by its ID.
     *  For X11 we use `wmctrl`; for Wayland a fallback is currently a no‑op.
     */
    bool setWindowPosition(const std::string& windowId, int monitorIndex);
};
