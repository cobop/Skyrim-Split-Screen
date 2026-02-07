#pragma once
#include <string>
#include <unistd.h>   // pid_t
#include "Config.h"

/*
 * SPDX-FileCopyrightText: 2026 Jane Doe
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

class GameInstance {
public:
    GameInstance() = default;
    ~GameInstance() = default;

    /** Launch a Skyrim instance using the provided configuration.
     *  Returns true on success, false otherwise.
     */
    bool launch(const Config& config, ScreenPlacement side);

    /** Terminate the running instance if any. */
    void terminate();

    /** Get the process ID of the launched instance. */
    pid_t getPid() const { return m_pid; }

    /** Get the window identifier (as a string) – placeholder for now. */
    std::string getWindowId() const { return m_windowId; }

private:
    pid_t m_pid{0};
    std::string m_windowId;   // In a real implementation this would be the X11/Wayland window id.
};
