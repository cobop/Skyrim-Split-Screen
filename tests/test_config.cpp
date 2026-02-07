#include <gtest/gtest.h>
#include "Config.h"
#include <nlohmann/json.hpp>
#include <fstream>

// Helper to write a temporary config file.
static std::string writeTempConfig(const std::string& content)
{
    std::string path = "temp_config.json";
    std::ofstream out(path);
    out << content;
    out.close();
    return path;
}

TEST(ConfigLoadSave, LoadDefaultWhenFileMissing)
{
    Config cfg = loadConfig("nonexistent.json");
    // Expect default values (empty strings and defaults)
    EXPECT_EQ(cfg.steam_app_id, "");
    EXPECT_EQ(cfg.proton_prefix, "");
    EXPECT_EQ(cfg.skyrim_together_url, "");
    EXPECT_EQ(cfg.launch_args, "");
    EXPECT_EQ(cfg.placement, ScreenPlacement::LEFT);
    EXPECT_EQ(cfg.monitor_left, 0);
    EXPECT_EQ(cfg.monitor_right, 1);
}

TEST(ConfigLoadSave, SaveAndLoad)
{
    Config original;
    original.steam_app_id = "123456";
    original.proton_prefix = "/path/to/prefix";
    original.skyrim_together_url = "https://example.com";
    original.launch_args = "-some -args";
    original.placement = ScreenPlacement::CUSTOM;
    original.monitor_left = 2;
    original.monitor_right = 3;

    std::string path = writeTempConfig("");
    saveConfig(original, path);

    Config loaded = loadConfig(path);
    EXPECT_EQ(loaded.steam_app_id, original.steam_app_id);
    EXPECT_EQ(loaded.proton_prefix, original.proton_prefix);
    EXPECT_EQ(loaded.skyrim_together_url, original.skyrim_together_url);
    EXPECT_EQ(loaded.launch_args, original.launch_args);
    EXPECT_EQ(loaded.placement, original.placement);
    EXPECT_EQ(loaded.monitor_left, original.monitor_left);
    EXPECT_EQ(loaded.monitor_right, original.monitor_right);
}
