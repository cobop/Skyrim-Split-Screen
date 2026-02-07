#include "Launcher.h"
#include <iostream>

/*
 * SPDX-FileCopyrightText: 2026 Jane Doe
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

Launcher::Launcher(const Config& config)
    : m_config(config)
{
    // Constructor can perform any necessary initialization.
    std::cout << "[Launcher] Initialized with Steam App ID: " << m_config.steam_app_id << std::endl;
}

bool Launcher::launchSkyrim(ScreenPlacement side)
{
    std::cout << "[Launcher] Request to launch Skyrim on side: "
              << (side == ScreenPlacement::LEFT ? "LEFT" : "RIGHT") << std::endl;

    // Choose the appropriate GameInstance based on the side.
    GameInstance* instance = (side == ScreenPlacement::LEFT) ? &m_leftInstance : &m_rightInstance;

    // Delegate the actual launch to the GameInstance.
    bool success = instance->launch(m_config, side);
    if (success) {
        std::cout << "[Launcher] Skyrim launched successfully (PID " << instance->getPid() << ")" << std::endl;
    } else {
        std::cerr << "[Launcher] Failed to launch Skyrim on side: "
                   << (side == ScreenPlacement::LEFT ? "LEFT" : "RIGHT") << std::endl;
    }
    return success;
}

void Launcher::stopAll()
{
    std::cout << "[Launcher] Stopping all Skyrim instances." << std::endl;
    m_leftInstance.terminate();
    m_rightInstance.terminate();
}
