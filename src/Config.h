#pragma once
#include <string>

/*
 * SPDX-FileCopyrightText: 2026 Jane Doe
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

enum class ScreenPlacement { LEFT, RIGHT, CUSTOM };

struct Config {
    std::string steam_app_id;          // e.g., "228200" for Skyrim Special Edition
    std::string proton_prefix;         // Path to Proton prefix
    std::string skyrim_together_url;   // Server URL
    std::string launch_args;           // Additional launch arguments
    ScreenPlacement placement;          // Enum: LEFT, RIGHT, CUSTOM
    int monitor_left;                  // X11 monitor index for first instance
    int monitor_right;                 // X11 monitor index for second instance
    std::string mo2_command;           // Command to launch Mod Organizer 2 (optional)
};

/// Load configuration from a JSON file.
Config loadConfig(const std::string& path);
/// Save configuration to a JSON file.
void saveConfig(const Config& config, const std::string& path);
