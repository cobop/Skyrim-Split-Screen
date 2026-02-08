#include "Config.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

/*
 * SPDX-FileCopyrightText: 2026 Jane Doe
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

using json = nlohmann::json;

Config loadConfig(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[Config] Could not open config file: " << path << ". Using default values.\n";
        return Config{};
    }

    json j;
    try {
        file >> j;
    } catch (const json::parse_error& e) {
        std::cerr << "[Config] JSON parse error in " << path << ": " << e.what() << ". Using default values.\n";
        return Config{};
    }

    Config cfg;
    cfg.steam_app_id = j.value("steam_app_id", "228200");
    cfg.proton_prefix = j.value("proton_prefix", "");
    cfg.skyrim_together_url = j.value("skyrim_together_url", "");
    cfg.launch_args = j.value("launch_args", "");
    cfg.mo2_command = j.value("mo2_command", "");
    std::string placementStr = j.value("placement", "LEFT");
    if (placementStr == "LEFT")
        cfg.placement = ScreenPlacement::LEFT;
    else if (placementStr == "RIGHT")
        cfg.placement = ScreenPlacement::RIGHT;
    else
        cfg.placement = ScreenPlacement::CUSTOM;

    cfg.monitor_left = j.value("monitor_left", 0);
    cfg.monitor_right = j.value("monitor_right", 1);

    return cfg;
}

void saveConfig(const Config& config, const std::string& path)
{
    json j;
    j["steam_app_id"] = config.steam_app_id;
    j["proton_prefix"] = config.proton_prefix;
    j["skyrim_together_url"] = config.skyrim_together_url;
    j["launch_args"] = config.launch_args;
    j["mo2_command"] = config.mo2_command;
    switch (config.placement) {
        case ScreenPlacement::LEFT:   j["placement"] = "LEFT"; break;
        case ScreenPlacement::RIGHT:  j["placement"] = "RIGHT"; break;
        case ScreenPlacement::CUSTOM: j["placement"] = "CUSTOM"; break;
    }
    j["monitor_left"] = config.monitor_left;
    j["monitor_right"] = config.monitor_right;

    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "[Config] Could not write to config file: " << path << "\n";
        return;
    }

    file << j.dump(4);
}
