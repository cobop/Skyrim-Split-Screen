#include "WindowManager.h"
#include <iostream>
#include <cstdlib>   // std::system
#include <sstream>

/*
 * SPDX-FileCopyrightText: 2026 Jane Doe
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

bool WindowManager::placeWindow(const GameInstance& instance, const Config& config, ScreenPlacement side)
{
    int monitor = (side == ScreenPlacement::LEFT) ? config.monitor_left : config.monitor_right;
    const std::string& windowId = instance.getWindowId();

    if (windowId.empty()) {
        std::cerr << "[WindowManager] No window ID available for the instance.\n";
        return false;
    }

    std::cout << "[WindowManager] Placing window " << windowId
              << " on monitor index " << monitor << " (side: "
              << (side == ScreenPlacement::LEFT ? "LEFT" : "RIGHT") << ")\n";

    return setWindowPosition(windowId, monitor);
}

bool WindowManager::setWindowPosition(const std::string& windowId, int monitorIndex)
{
    // Stub implementation: print the command that would be executed.
    // A real implementation would query window geometry and use wmctrl/xrandr.

    std::ostringstream cmd;
    // Example using wmctrl to move a window to a specific monitor (X11):
    // This command is illustrative; actual parameters may differ.
    cmd << "wmctrl -ir " << windowId << " -e 0,"
        << (monitorIndex * 1920) << ",0,-1,-1"; // assuming 1920px monitor width

    std::cout << "[WindowManager] Executing command: " << cmd.str() << std::endl;

    // For now we just simulate success.
    // In a real scenario you might use std::system(cmd.str().c_str()) and check the result.
    return true;
}
