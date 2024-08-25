#include "config.h"

// Global config instance
Config global_config;

void save_config(const std::string& filename) {
    nlohmann::json j;

    // Serialize the global_config object
    j["show_menu"] = global_config.show_menu;

    j["enable_esp"] = global_config.enable_esp;
    j["enable_skeleton"] = global_config.enable_skeleton;
    j["enemy_health_bar_esp"] = global_config.enemy_health_bar_esp;
    j["enemy_armor_bar_esp"] = global_config.enemy_armor_bar_esp;
    j["health_text_esp"] = global_config.health_text_esp;
    j["enable_fov"] = global_config.enable_fov;
    j["enable_slow_fov"] = global_config.enable_slow_fov;

    j["enable_snaplines"] = global_config.enable_snaplines;
    j["enemy_snaplines"] = global_config.enemy_snaplines;
    j["team_snaplines"] = global_config.team_snaplines;

    j["enable_aimbot"] = global_config.enable_aimbot;
    j["enable_aimlock"] = global_config.enable_aimlock;

    j["triggerbot"] = global_config.triggerbot;
    j["enable_radar"] = global_config.enable_radar;
    j["game_radar"] = global_config.game_radar;
    j["triggerbot"] = global_config.triggerbot;
    j["enable_radar"] = global_config.enable_radar;
    j["game_radar"] = global_config.game_radar;
    j["custom_radar"] = global_config.custom_radar;
    j["bomb_timer"] = global_config.bomb_timer;
    j["no_flash"] = global_config.no_flash;
    j["bhop"] = global_config.bhop;
    j["enable_bhop"] = global_config.enable_bhop;
    j["enable_name_esp"] = global_config.enable_name_esp;

    // Combo indexes
    j["combo_index"] = global_config.combo_index;
    j["combo_index_esp"] = global_config.combo_index_esp;
    j["combo_index_skeleton_color"] = global_config.combo_index_skeleton_color;
    j["line_index"] = global_config.line_index;

    // Color settings
    j["color_esp"] = { global_config.color_esp[0], global_config.color_esp[1], global_config.color_esp[2], global_config.color_esp[3] };
    j["color_skeleton"] = { global_config.color_skeleton[0], global_config.color_skeleton[1], global_config.color_skeleton[2], global_config.color_skeleton[3] };
    j["color_snapline"] = { global_config.color_snapline[0], global_config.color_snapline[1], global_config.color_snapline[2], global_config.color_snapline[3] };

    j["distance_to_head"] = global_config.distance_to_head;
    j["fov_value"] = global_config.fov_value;
    j["enable_thirdperson"] = global_config.enable_thirdperson;

    j["fov_radius"] = global_config.fov_radius;
    j["hit_chance"] = global_config.hit_chance;
    j["smooth_index"] = global_config.smooth_index;

    // Menu color customization
    j["menu_button_color"] = { global_config.menu_button_color[0], global_config.menu_button_color[1], global_config.menu_button_color[2], global_config.menu_button_color[3] };
    j["menu_button_hovered_color"] = { global_config.menu_button_hovered_color[0], global_config.menu_button_hovered_color[1], global_config.menu_button_hovered_color[2], global_config.menu_button_hovered_color[3] };
    j["menu_button_active_color"] = { global_config.menu_button_active_color[0], global_config.menu_button_active_color[1], global_config.menu_button_active_color[2], global_config.menu_button_active_color[3] };
    j["menu_background_color"] = { global_config.menu_background_color[0], global_config.menu_background_color[1], global_config.menu_background_color[2], global_config.menu_background_color[3] };
    j["menu_header_color"] = { global_config.menu_header_color[0], global_config.menu_header_color[1], global_config.menu_header_color[2], global_config.menu_header_color[3] };

    // Additional customizable colors
    j["menu_text_color"] = { global_config.menu_text_color[0], global_config.menu_text_color[1], global_config.menu_text_color[2], global_config.menu_text_color[3] };
    j["menu_border_color"] = { global_config.menu_border_color[0], global_config.menu_border_color[1], global_config.menu_border_color[2], global_config.menu_border_color[3] };
    j["menu_scrollbar_color"] = { global_config.menu_scrollbar_color[0], global_config.menu_scrollbar_color[1], global_config.menu_scrollbar_color[2], global_config.menu_scrollbar_color[3] };
    j["menu_scrollbar_grab_color"] = { global_config.menu_scrollbar_grab_color[0], global_config.menu_scrollbar_grab_color[1], global_config.menu_scrollbar_grab_color[2], global_config.menu_scrollbar_grab_color[3] };
    j["menu_scrollbar_grab_hovered_color"] = { global_config.menu_scrollbar_grab_hovered_color[0], global_config.menu_scrollbar_grab_hovered_color[1], global_config.menu_scrollbar_grab_hovered_color[2], global_config.menu_scrollbar_grab_hovered_color[3] };
    j["menu_scrollbar_grab_active_color"] = { global_config.menu_scrollbar_grab_active_color[0], global_config.menu_scrollbar_grab_active_color[1], global_config.menu_scrollbar_grab_active_color[2], global_config.menu_scrollbar_grab_active_color[3] };

    j["menu_title_color"] = { global_config.menu_title_color[0], global_config.menu_title_color[1], global_config.menu_title_color[2], global_config.menu_title_color[3] };
    j["menu_tooltip_color"] = { global_config.menu_tooltip_color[0], global_config.menu_tooltip_color[1], global_config.menu_tooltip_color[2], global_config.menu_tooltip_color[3] };
    j["menu_tooltip_text_color"] = { global_config.menu_tooltip_text_color[0], global_config.menu_tooltip_text_color[1], global_config.menu_tooltip_text_color[2], global_config.menu_tooltip_text_color[3] };
    j["menu_slider_color"] = { global_config.menu_slider_color[0], global_config.menu_slider_color[1], global_config.menu_slider_color[2], global_config.menu_slider_color[3] };
    j["menu_slider_hovered_color"] = { global_config.menu_slider_hovered_color[0], global_config.menu_slider_hovered_color[1], global_config.menu_slider_hovered_color[2], global_config.menu_slider_hovered_color[3] };
    j["menu_slider_active_color"] = { global_config.menu_slider_active_color[0], global_config.menu_slider_active_color[1], global_config.menu_slider_active_color[2], global_config.menu_slider_active_color[3] };

    j["menu_tab_color"] = { global_config.menu_tab_color[0], global_config.menu_tab_color[1], global_config.menu_tab_color[2], global_config.menu_tab_color[3] };
    j["menu_tab_hovered_color"] = { global_config.menu_tab_hovered_color[0], global_config.menu_tab_hovered_color[1], global_config.menu_tab_hovered_color[2], global_config.menu_tab_hovered_color[3] };
    j["menu_tab_active_color"] = { global_config.menu_tab_active_color[0], global_config.menu_tab_active_color[1], global_config.menu_tab_active_color[2], global_config.menu_tab_active_color[3] };
    j["menu_checkbox_color"] = { global_config.menu_checkbox_color[0], global_config.menu_checkbox_color[1], global_config.menu_checkbox_color[2], global_config.menu_checkbox_color[3] };
    j["menu_checkbox_hovered_color"] = { global_config.menu_checkbox_hovered_color[0], global_config.menu_checkbox_hovered_color[1], global_config.menu_checkbox_hovered_color[2], global_config.menu_checkbox_hovered_color[3] };
    j["menu_checkbox_active_color"] = { global_config.menu_checkbox_active_color[0], global_config.menu_checkbox_active_color[1], global_config.menu_checkbox_active_color[2], global_config.menu_checkbox_active_color[3] };

    j["menu_radio_color"] = { global_config.menu_radio_color[0], global_config.menu_radio_color[1], global_config.menu_radio_color[2], global_config.menu_radio_color[3] };
    j["menu_radio_hovered_color"] = { global_config.menu_radio_hovered_color[0], global_config.menu_radio_hovered_color[1], global_config.menu_radio_hovered_color[2], global_config.menu_radio_hovered_color[3] };
    j["menu_radio_active_color"] = { global_config.menu_radio_active_color[0], global_config.menu_radio_active_color[1], global_config.menu_radio_active_color[2], global_config.menu_radio_active_color[3] };
    j["menu_progress_color"] = { global_config.menu_progress_color[0], global_config.menu_progress_color[1], global_config.menu_progress_color[2], global_config.menu_progress_color[3] };
    j["menu_progress_filled_color"] = { global_config.menu_progress_filled_color[0], global_config.menu_progress_filled_color[1], global_config.menu_progress_filled_color[2], global_config.menu_progress_filled_color[3] };

    j["primary_color"] = { global_config.primary_color[0], global_config.primary_color[1], global_config.primary_color[2], global_config.primary_color[3] };

    // Save JSON to file
    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);  // 4 spaces for indentation
        file.close();
    }
}

void load_config(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        nlohmann::json j;
        file >> j;
        file.close();

        // Deserialize the global_config object
        global_config.show_menu = j.value("show_menu", false);

        global_config.enable_esp = j.value("enable_esp", false);
        global_config.enable_skeleton = j.value("enable_skeleton", false);
        global_config.enemy_health_bar_esp = j.value("enemy_health_bar_esp", false);
        global_config.enemy_armor_bar_esp = j.value("enemy_armor_bar_esp", false);
        global_config.health_text_esp = j.value("health_text_esp", false);
        global_config.enable_fov = j.value("enable_fov", false);

        global_config.enable_snaplines = j.value("enable_snaplines", false);
        global_config.enemy_snaplines = j.value("enemy_snaplines", false);
        global_config.team_snaplines = j.value("team_snaplines", false);

        global_config.enable_aimbot = j.value("enable_aimbot", false);
        global_config.enable_aimlock = j.value("enable_aimlock", false);
        global_config.enable_slow_fov = j.value("enable_slow_fov", true);

        global_config.triggerbot = j.value("triggerbot", false);
        global_config.enable_radar = j.value("enable_radar", false);
        global_config.game_radar = j.value("game_radar", false);
        global_config.custom_radar = j.value("custom_radar", false);
        global_config.bomb_timer = j.value("bomb_timer", false);
        global_config.no_flash = j.value("no_flash", false);
        global_config.bhop = j.value("bhop", false);
        global_config.enable_bhop = j.value("enable_bhop", false);
        global_config.enable_name_esp = j.value("enable_name_esp", false);

        global_config.combo_index = j.value("combo_index", 0);
        global_config.combo_index_esp = j.value("combo_index_esp", 0);
        global_config.combo_index_skeleton_color = j.value("combo_index_skeleton_color", 0);
        global_config.line_index = j.value("line_index", 4.0f);

        // Deserialize color arrays
        auto color_esp = j.value("color_esp", std::vector<float>{1.0f, 0.0f, 0.0f, 0.0f});
        if (color_esp.size() == 4) {
            std::copy(color_esp.begin(), color_esp.end(), global_config.color_esp);
        }

        auto color_skeleton = j.value("color_skeleton", std::vector<float>{1.0f, 0.0f, 0.0f, 0.0f});
        if (color_skeleton.size() == 4) {
            std::copy(color_skeleton.begin(), color_skeleton.end(), global_config.color_skeleton);
        }

        auto color_snapline = j.value("color_snapline", std::vector<float>{1.0f, 0.0f, 0.0f, 0.0f});
        if (color_snapline.size() == 4) {
            std::copy(color_snapline.begin(), color_snapline.end(), global_config.color_snapline);
        }

        global_config.distance_to_head = j.value("distance_to_head", 75.0f);
        global_config.fov_value = j.value("fov_value", 90);
        global_config.enable_thirdperson = j.value("enable_thirdperson", false);

        global_config.fov_radius = j.value("fov_radius", 100.0f);
        global_config.hit_chance = j.value("hit_chance", 100.0f);
        global_config.smooth_index = j.value("smooth_index", 1.0f);

        // Deserialize menu color customization
        auto menu_button_color = j.value("menu_button_color", std::vector<float>{0.10f, 0.10f, 0.10f, 1.00f});
        if (menu_button_color.size() == 4) {
            std::copy(menu_button_color.begin(), menu_button_color.end(), global_config.menu_button_color);
        }

        auto menu_button_hovered_color = j.value("menu_button_hovered_color", std::vector<float>{0.20f, 0.20f, 0.20f, 1.00f});
        if (menu_button_hovered_color.size() == 4) {
            std::copy(menu_button_hovered_color.begin(), menu_button_hovered_color.end(), global_config.menu_button_hovered_color);
        }

        auto menu_button_active_color = j.value("menu_button_active_color", std::vector<float>{0.30f, 0.30f, 0.30f, 1.00f});
        if (menu_button_active_color.size() == 4) {
            std::copy(menu_button_active_color.begin(), menu_button_active_color.end(), global_config.menu_button_active_color);
        }

        auto menu_background_color = j.value("menu_background_color", std::vector<float>{0.05f, 0.05f, 0.05f, 1.00f});
        if (menu_background_color.size() == 4) {
            std::copy(menu_background_color.begin(), menu_background_color.end(), global_config.menu_background_color);
        }

        auto menu_header_color = j.value("menu_header_color", std::vector<float>{0.10f, 0.10f, 0.10f, 1.00f});
        if (menu_header_color.size() == 4) {
            std::copy(menu_header_color.begin(), menu_header_color.end(), global_config.menu_header_color);
        }

        // Deserialize additional customizable colors
        auto menu_text_color = j.value("menu_text_color", std::vector<float>{1.00f, 1.00f, 1.00f, 1.00f});
        if (menu_text_color.size() == 4) {
            std::copy(menu_text_color.begin(), menu_text_color.end(), global_config.menu_text_color);
        }

        auto menu_border_color = j.value("menu_border_color", std::vector<float>{0.25f, 0.25f, 0.25f, 1.00f});
        if (menu_border_color.size() == 4) {
            std::copy(menu_border_color.begin(), menu_border_color.end(), global_config.menu_border_color);
        }

        auto menu_scrollbar_color = j.value("menu_scrollbar_color", std::vector<float>{0.15f, 0.15f, 0.15f, 1.00f});
        if (menu_scrollbar_color.size() == 4) {
            std::copy(menu_scrollbar_color.begin(), menu_scrollbar_color.end(), global_config.menu_scrollbar_color);
        }

        auto menu_scrollbar_grab_color = j.value("menu_scrollbar_grab_color", std::vector<float>{0.20f, 0.20f, 0.20f, 1.00f});
        if (menu_scrollbar_grab_color.size() == 4) {
            std::copy(menu_scrollbar_grab_color.begin(), menu_scrollbar_grab_color.end(), global_config.menu_scrollbar_grab_color);
        }

        auto menu_scrollbar_grab_hovered_color = j.value("menu_scrollbar_grab_hovered_color", std::vector<float>{0.30f, 0.30f, 0.30f, 1.00f});
        if (menu_scrollbar_grab_hovered_color.size() == 4) {
            std::copy(menu_scrollbar_grab_hovered_color.begin(), menu_scrollbar_grab_hovered_color.end(), global_config.menu_scrollbar_grab_hovered_color);
        }

        auto menu_scrollbar_grab_active_color = j.value("menu_scrollbar_grab_active_color", std::vector<float>{0.40f, 0.40f, 0.40f, 1.00f});
        if (menu_scrollbar_grab_active_color.size() == 4) {
            std::copy(menu_scrollbar_grab_active_color.begin(), menu_scrollbar_grab_active_color.end(), global_config.menu_scrollbar_grab_active_color);
        }

        auto menu_title_color = j.value("menu_title_color", std::vector<float>{0.40f, 0.40f, 0.40f, 1.00f});
        if (menu_title_color.size() == 4) {
            std::copy(menu_title_color.begin(), menu_title_color.end(), global_config.menu_title_color);
        }

        auto menu_tooltip_color = j.value("menu_tooltip_color", std::vector<float>{0.20f, 0.20f, 0.20f, 1.00f});
        if (menu_tooltip_color.size() == 4) {
            std::copy(menu_tooltip_color.begin(), menu_tooltip_color.end(), global_config.menu_tooltip_color);
        }

        auto menu_tooltip_text_color = j.value("menu_tooltip_text_color", std::vector<float>{1.00f, 1.00f, 1.00f, 1.00f});
        if (menu_tooltip_text_color.size() == 4) {
            std::copy(menu_tooltip_text_color.begin(), menu_tooltip_text_color.end(), global_config.menu_tooltip_text_color);
        }

        auto menu_slider_color = j.value("menu_slider_color", std::vector<float>{0.30f, 0.30f, 0.30f, 1.00f});
        if (menu_slider_color.size() == 4) {
            std::copy(menu_slider_color.begin(), menu_slider_color.end(), global_config.menu_slider_color);
        }

        auto menu_slider_hovered_color = j.value("menu_slider_hovered_color", std::vector<float>{0.40f, 0.40f, 0.40f, 1.00f});
        if (menu_slider_hovered_color.size() == 4) {
            std::copy(menu_slider_hovered_color.begin(), menu_slider_hovered_color.end(), global_config.menu_slider_hovered_color);
        }

        auto menu_slider_active_color = j.value("menu_slider_active_color", std::vector<float>{0.50f, 0.50f, 0.50f, 1.00f});
        if (menu_slider_active_color.size() == 4) {
            std::copy(menu_slider_active_color.begin(), menu_slider_active_color.end(), global_config.menu_slider_active_color);
        }

        auto menu_tab_color = j.value("menu_tab_color", std::vector<float>{0.15f, 0.15f, 0.15f, 1.00f});
        if (menu_tab_color.size() == 4) {
            std::copy(menu_tab_color.begin(), menu_tab_color.end(), global_config.menu_tab_color);
        }

        auto menu_tab_hovered_color = j.value("menu_tab_hovered_color", std::vector<float>{0.25f, 0.25f, 0.25f, 1.00f});
        if (menu_tab_hovered_color.size() == 4) {
            std::copy(menu_tab_hovered_color.begin(), menu_tab_hovered_color.end(), global_config.menu_tab_hovered_color);
        }

        auto menu_tab_active_color = j.value("menu_tab_active_color", std::vector<float>{0.35f, 0.35f, 0.35f, 1.00f});
        if (menu_tab_active_color.size() == 4) {
            std::copy(menu_tab_active_color.begin(), menu_tab_active_color.end(), global_config.menu_tab_active_color);
        }

        auto menu_checkbox_color = j.value("menu_checkbox_color", std::vector<float>{0.20f, 0.20f, 0.20f, 1.00f});
        if (menu_checkbox_color.size() == 4) {
            std::copy(menu_checkbox_color.begin(), menu_checkbox_color.end(), global_config.menu_checkbox_color);
        }

        auto menu_checkbox_hovered_color = j.value("menu_checkbox_hovered_color", std::vector<float>{0.30f, 0.30f, 0.30f, 1.00f});
        if (menu_checkbox_hovered_color.size() == 4) {
            std::copy(menu_checkbox_hovered_color.begin(), menu_checkbox_hovered_color.end(), global_config.menu_checkbox_hovered_color);
        }

        auto menu_checkbox_active_color = j.value("menu_checkbox_active_color", std::vector<float>{0.40f, 0.40f, 0.40f, 1.00f});
        if (menu_checkbox_active_color.size() == 4) {
            std::copy(menu_checkbox_active_color.begin(), menu_checkbox_active_color.end(), global_config.menu_checkbox_active_color);
        }

        auto menu_radio_color = j.value("menu_radio_color", std::vector<float>{0.20f, 0.20f, 0.20f, 1.00f});
        if (menu_radio_color.size() == 4) {
            std::copy(menu_radio_color.begin(), menu_radio_color.end(), global_config.menu_radio_color);
        }

        auto menu_radio_hovered_color = j.value("menu_radio_hovered_color", std::vector<float>{0.30f, 0.30f, 0.30f, 1.00f});
        if (menu_radio_hovered_color.size() == 4) {
            std::copy(menu_radio_hovered_color.begin(), menu_radio_hovered_color.end(), global_config.menu_radio_hovered_color);
        }

        auto menu_radio_active_color = j.value("menu_radio_active_color", std::vector<float>{0.40f, 0.40f, 0.40f, 1.00f});
        if (menu_radio_active_color.size() == 4) {
            std::copy(menu_radio_active_color.begin(), menu_radio_active_color.end(), global_config.menu_radio_active_color);
        }

        auto menu_progress_color = j.value("menu_progress_color", std::vector<float>{0.25f, 0.25f, 0.25f, 1.00f});
        if (menu_progress_color.size() == 4) {
            std::copy(menu_progress_color.begin(), menu_progress_color.end(), global_config.menu_progress_color);
        }

        auto menu_progress_filled_color = j.value("menu_progress_filled_color", std::vector<float>{0.35f, 0.35f, 0.35f, 1.00f});
        if (menu_progress_filled_color.size() == 4) {
            std::copy(menu_progress_filled_color.begin(), menu_progress_filled_color.end(), global_config.menu_progress_filled_color);
        }

        auto primary_color = j.value("primary_color", std::vector<float>{0.8f, 0.0f, 0.0f, 1.00f});
        if (primary_color.size() == 4) {
            std::copy(primary_color.begin(), primary_color.end(), global_config.primary_color);
        }
    }
}

std::vector<std::string> get_saved_configs() {
    std::vector<std::string> configs;
    std::string path = "./configs/";

    // Check if directory exists
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
    }

    // Iterate over all files in the directory
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (filename.size() > 5 && filename.substr(filename.size() - 5) == ".json") {
                configs.push_back(filename.substr(0, filename.size() - 5));
            }
        }
    }

    return configs;
}

