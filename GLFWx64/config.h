#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <filesystem> // For file system operations

// Global config instance
extern struct Config global_config;

// Configuration structure
struct Config {
    // General settings
    bool show_menu = false;

    // ESP settings
    bool enable_esp = false;
    bool enable_skeleton = false;
    bool enemy_health_bar_esp = false;
    bool enemy_armor_bar_esp = false;
    bool health_text_esp = false;
    bool enable_fov = false;

    // Snapline settings
    bool enable_snaplines = false;
    bool enemy_snaplines = false;
    bool team_snaplines = false;

    // Aimbot settings
    bool enable_aimbot = false;
    bool enable_aimlock = false;

    // Miscellaneous settings
    bool triggerbot = false;
    bool enable_radar = false;
    bool game_radar = false;
    bool custom_radar = false;
    bool bomb_timer = false;
    bool no_flash = false;
    bool bhop = false;
    bool enable_bhop = false;
    bool enable_name_esp = false;

    bool enable_slow_fov = true;

    // Combo indexes
    int combo_index = 0;
    int combo_index_esp = 0;
    int combo_index_skeleton_color = 0;
    float line_index = 4.0f;

    // Combo items
    const char* combo_items_snapline[3] = { "Top", "Center", "Bottom" };
    const char* combo_items_skeleton_color[8] = { "Glow", "Rainbow", "Pulse", "Dynamic Color Shift", "Outer Glow", "Strobe", "Gradient", "Normal" };
    const char* combo_items_esp[3] = { "Outline", "Corners", "Box" };

    // Color settings
    float color_esp[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    float color_skeleton[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    float color_snapline[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    float distance_to_head = 75.0f;

    uint32_t fov_value = 90;
    uint32_t max_value = 150;
    uint32_t min_value = 70;
    bool enable_thirdperson = false;

    float fov_radius = 100.0f;
    float hit_chance = 100.0f;
    float smooth_index = 1.0f;

    // Menu color customization
    float menu_button_color[4] = { 0.10f, 0.10f, 0.10f, 1.00f };
    float menu_button_hovered_color[4] = { 0.20f, 0.20f, 0.20f, 1.00f };
    float menu_button_active_color[4] = { 0.30f, 0.30f, 0.30f, 1.00f };
    float menu_background_color[4] = { 0.05f, 0.05f, 0.05f, 1.00f };
    float menu_header_color[4] = { 0.10f, 0.10f, 0.10f, 1.00f };

    // Additional customizable colors
    float menu_text_color[4] = { 1.00f, 1.00f, 1.00f, 1.00f };
    float menu_border_color[4] = { 0.25f, 0.25f, 0.25f, 1.00f };
    float menu_scrollbar_color[4] = { 0.15f, 0.15f, 0.15f, 1.00f };
    float menu_scrollbar_grab_color[4] = { 0.20f, 0.20f, 0.20f, 1.00f };
    float menu_scrollbar_grab_hovered_color[4] = { 0.30f, 0.30f, 0.30f, 1.00f };
    float menu_scrollbar_grab_active_color[4] = { 0.40f, 0.40f, 0.40f, 1.00f };

    float menu_title_color[4] = { 0.40f, 0.40f, 0.40f, 1.00f };
    float menu_tooltip_color[4] = { 0.20f, 0.20f, 0.20f, 1.00f };
    float menu_tooltip_text_color[4] = { 1.00f, 1.00f, 1.00f, 1.00f };
    float menu_slider_color[4] = { 0.30f, 0.30f, 0.30f, 1.00f };
    float menu_slider_hovered_color[4] = { 0.40f, 0.40f, 0.40f, 1.00f };
    float menu_slider_active_color[4] = { 0.50f, 0.50f, 0.50f, 1.00f };

    float menu_tab_color[4] = { 0.15f, 0.15f, 0.15f, 1.00f };
    float menu_tab_hovered_color[4] = { 0.25f, 0.25f, 0.25f, 1.00f };
    float menu_tab_active_color[4] = { 0.35f, 0.35f, 0.35f, 1.00f };
    float menu_checkbox_color[4] = { 0.20f, 0.20f, 0.20f, 1.00f };
    float menu_checkbox_hovered_color[4] = { 0.30f, 0.30f, 0.30f, 1.00f };
    float menu_checkbox_active_color[4] = { 0.40f, 0.40f, 0.40f, 1.00f };

    float menu_radio_color[4] = { 0.20f, 0.20f, 0.20f, 1.00f };
    float menu_radio_hovered_color[4] = { 0.30f, 0.30f, 0.30f, 1.00f };
    float menu_radio_active_color[4] = { 0.40f, 0.40f, 0.40f, 1.00f };
    float menu_progress_color[4] = { 0.25f, 0.25f, 0.25f, 1.00f };
    float menu_progress_filled_color[4] = { 0.35f, 0.35f, 0.35f, 1.00f };

    // Primary color
    float primary_color[4] = { 0.8f, 0.0f, 0.0f, 1.00f }; // Default to blood neon red
};



// Function to get the saved configurations from the filesystem
std::vector<std::string> get_saved_configs();

// Save the current configuration to a file
void save_config(const std::string& filename);

// Load a configuration from a file
void load_config(const std::string& filename);