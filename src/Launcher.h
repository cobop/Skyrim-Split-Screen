#pragma once
#include "Config.h"
#include "GameInstance.h"
#include <string>
#include <iostream>

/*
 * SPDX-FileCopyrightText: 2026 Jane Doe
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

class Launcher {
public:
    explicit Launcher(const Config& config);
    bool launchSkyrim(ScreenPlacement side);
    void stopAll();

private:
    Config m_config;
    GameInstance m_leftInstance;
    GameInstance m_rightInstance;
};
