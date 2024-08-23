#include "menu.h"
#include "config.h"
#include <filesystem>
#include <vector>
#include <string>

// Function to hide the menu
void menu::HideMenu(GLFWwindow* Window) {
    glfwSetWindowAttrib(Window, GLFW_MOUSE_PASSTHROUGH, true);
}

// Function to show the menu
void menu::ShowMenu(GLFWwindow* Window) {
    glfwSetWindowAttrib(Window, GLFW_MOUSE_PASSTHROUGH, false);
}

// Function to convert ImGuiKey to a string for display
const char* GetKeyName(ImGuiKey key) {
    if (key == ImGuiKey_None)
        return "None";
    return ImGui::GetKeyName(key);
}

// Render the main menu
void menu::Render() {
    

    static int selectedTab = 0;
    static char config_name[128] = "";
    static std::vector<std::string> available_configs = get_saved_configs();
    static int selected_config = -1;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(800.0f, 500.0f));
    ImGui::Begin("ZENITH", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

    ApplyCustomColors();

    // Tabs
    ImGui::BeginChild("Tabs", ImVec2(150, 0), true, ImGuiWindowFlags_NoScrollbar);

    if (ImGui::Button("Aimbot", ImVec2(150, 45))) {
        selectedTab = 0;
    }
    if (ImGui::Button("Visuals", ImVec2(150, 45))) {
        selectedTab = 1;
    }
    if (ImGui::Button("Misc", ImVec2(150, 45))) {
        selectedTab = 2;
    }
    if (ImGui::Button("Settings", ImVec2(150, 45))) {
        selectedTab = 3;
    }
    ImGui::EndChild();

    ImGui::SameLine();

    // Main Content
    ImGui::BeginGroup();
    ImGui::BeginChild("MainContent", ImVec2(600, 0), true, ImGuiWindowFlags_NoScrollbar);

    switch (selectedTab) {
    case 0: // Aimbot
        ImGui::Text("Legit");
        ImGui::Separator();
        ImGui::Checkbox("Aimbot", &global_config.enable_aimbot);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Enable aimbot functionality");
            ImGui::EndTooltip();
        }
        ImGui::Checkbox("Triggerbot", &global_config.triggerbot);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Automatically shoot when aiming at an enemy");
            ImGui::EndTooltip();
        }
        ImGui::SliderFloat("FOV", &global_config.fov_radius, 0.0f, 180.0f, "FOV: %.1f");
        ImGui::SliderFloat("Smoothness", &global_config.smooth_index, 1.0f, 10.0f, "Smoothness: %.1f");
        ImGui::Text("Rage");
        ImGui::Separator();
        ImGui::Checkbox("Aimlock", &global_config.enable_aimlock);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Lock your aim on the nearest enemy");
            ImGui::EndTooltip();
        }
        break;

    case 1: // Visuals
        ImGui::Text("ESP");
        ImGui::Separator();
        ImGui::Checkbox("Enable ESP", &global_config.enable_esp);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Show enemies through walls");
            ImGui::EndTooltip();
        }
        ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - ImGui::CalcItemWidth());
        ImGui::ColorEdit4("##EspColor", global_config.color_esp, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Change the color of ESP");
            ImGui::EndTooltip();
        }

        ImGui::Checkbox("Skeleton", &global_config.enable_skeleton);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Show skeletons of enemies");
            ImGui::EndTooltip();
        }
        ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - ImGui::CalcItemWidth());
        ImGui::ColorEdit4("##SkeletonColor", global_config.color_skeleton, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Change the color of skeletons");
            ImGui::EndTooltip();
        }

        ImGui::Combo("Skeleton Color Effect", &global_config.combo_index_skeleton_color, global_config.combo_items_skeleton_color, IM_ARRAYSIZE(global_config.combo_items_skeleton_color));
        ImGui::Combo("Combo ESP", &global_config.combo_index_esp, global_config.combo_items_esp, IM_ARRAYSIZE(global_config.combo_items_esp));
        ImGui::SliderFloat("Corner Line Index", &global_config.line_index, 1.0f, 10.0f);

        ImGui::Separator();
        ImGui::Checkbox("Snaplines", &global_config.enable_snaplines);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Draw snaplines to enemies");
            ImGui::EndTooltip();
        }
        ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - ImGui::CalcItemWidth());
        ImGui::ColorEdit4("##SnaplinesColor", global_config.color_snapline, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Change the color of snaplines");
            ImGui::EndTooltip();
        }
        ImGui::Combo("Combo Snaplines", &global_config.combo_index, global_config.combo_items_snapline, IM_ARRAYSIZE(global_config.combo_items_snapline)); // Adjusted combo box length
        ImGui::Separator();
        ImGui::Checkbox("Health Bar", &global_config.enemy_health_bar_esp);
        ImGui::Checkbox("Armor Bar", &global_config.enemy_armor_bar_esp);
        ImGui::Checkbox("Health Text", &global_config.health_text_esp);
        ImGui::Checkbox("Name Text", &global_config.enable_name_esp);
        ImGui::Checkbox("Radar", &global_config.enable_radar);
        break;

    case 2: // Misc
        ImGui::Text("Miscellaneous");
        ImGui::Separator();
        ImGui::Checkbox("Bomb Timer", &global_config.bomb_timer);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Show the time remaining for the bomb");
            ImGui::EndTooltip();
        }
        ImGui::Checkbox("No Flash", &global_config.no_flash);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Prevent screen from going white from flashbangs");
            ImGui::EndTooltip();
        }
        ImGui::Checkbox("Bhop", &global_config.enable_bhop);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Enable automatic bunny hopping");
            ImGui::EndTooltip();
        }
        ImGui::Checkbox("Fov", &global_config.enable_fov);
        ImGui::SliderScalar("Slider Label", ImGuiDataType_U32, &global_config.fov_value, &global_config.min_value, &global_config.max_value);
        ImGui::Checkbox("Enable Slow Fov to save performance", &global_config.enable_slow_fov);
        break;

    case 3: // Settings
        ImGui::Text("Settings");
        ImGui::Separator();

        ImGui::InputText("Config Name", config_name, IM_ARRAYSIZE(config_name));
        if (ImGui::Button("Save Config")) {
            std::string filename = std::string("./configs/") + config_name + ".json";
            save_config(filename);
            available_configs = get_saved_configs(); // Update the list of available configs
        }
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Save current settings with a custom name");
            ImGui::EndTooltip();
        }

        // Convert available_configs to an array of const char*
        std::vector<const char*> config_items;
        for (const auto& config : available_configs) {
            config_items.push_back(config.c_str());
        }

        if (ImGui::Combo("Load Config", &selected_config, config_items.data(), static_cast<int>(config_items.size()))) {
            if (selected_config >= 0 && selected_config < available_configs.size()) {
                std::string filename = std::string("./configs/") + available_configs[selected_config] + ".json";
                load_config(filename);
            }
        }
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Select and load a saved configuration");
            ImGui::EndTooltip();
        }

        ImGui::Separator();

        // Color Customization
        ImGui::Text("Customize Menu Colors");
        ImGui::Spacing();

        ImGui::ColorEdit4("Button Color", global_config.menu_button_color);
        ImGui::ColorEdit4("Button Hovered Color", global_config.menu_button_hovered_color);
        ImGui::ColorEdit4("Button Active Color", global_config.menu_button_active_color);
        ImGui::ColorEdit4("Background Color", global_config.menu_background_color);
        ImGui::ColorEdit4("Header Color", global_config.menu_header_color);
        ImGui::ColorEdit4("Menu Text Color", global_config.menu_text_color);
        ImGui::ColorEdit4("Menu Border Color", global_config.menu_border_color);
        ImGui::ColorEdit4("Scrollbar Color", global_config.menu_scrollbar_color);
        ImGui::ColorEdit4("Scrollbar Grab Color", global_config.menu_scrollbar_grab_color);
        ImGui::ColorEdit4("Scrollbar Grab Hovered Color", global_config.menu_scrollbar_grab_hovered_color);
        ImGui::ColorEdit4("Scrollbar Grab Active Color", global_config.menu_scrollbar_grab_active_color);
        ImGui::ColorEdit4("Title Color", global_config.menu_title_color);
        ImGui::ColorEdit4("Tooltip Color", global_config.menu_tooltip_color);
        ImGui::ColorEdit4("Tooltip Text Color", global_config.menu_tooltip_text_color);
        ImGui::ColorEdit4("Slider Color", global_config.menu_slider_color);
        ImGui::ColorEdit4("Slider Hovered Color", global_config.menu_slider_hovered_color);
        ImGui::ColorEdit4("Slider Active Color", global_config.menu_slider_active_color);
        ImGui::ColorEdit4("Tab Color", global_config.menu_tab_color);
        ImGui::ColorEdit4("Tab Hovered Color", global_config.menu_tab_hovered_color);
        ImGui::ColorEdit4("Tab Active Color", global_config.menu_tab_active_color);
        ImGui::ColorEdit4("Checkbox Color", global_config.menu_checkbox_color);
        ImGui::ColorEdit4("Checkbox Hovered Color", global_config.menu_checkbox_hovered_color);
        ImGui::ColorEdit4("Checkbox Active Color", global_config.menu_checkbox_active_color);
        ImGui::ColorEdit4("Radio Color", global_config.menu_radio_color);
        ImGui::ColorEdit4("Radio Hovered Color", global_config.menu_radio_hovered_color);
        ImGui::ColorEdit4("Radio Active Color", global_config.menu_radio_active_color);
        ImGui::ColorEdit4("Progress Color", global_config.menu_progress_color);
        ImGui::ColorEdit4("Progress Filled Color", global_config.menu_progress_filled_color);

        ImGui::Spacing();
        break;
    }

    ImGui::EndChild();
    ImGui::EndGroup();
    ImGui::End();

    ImGui::PopStyleVar();
}

void menu::RenderSecondaryWindow() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(200.f, 70.f));
    ImGui::Begin("Another Window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    float progress = client.iBombTickTime / 40.0f;

    ImGui::Text("Bomb Timer");
    ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f), std::to_string(40 - client.iBombTickTime).c_str());

    ImGui::End();
    ImGui::PopStyleVar();
}


// Function to apply custom colors to the menu
void menu::ApplyCustomColors() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Apply custom colors
    colors[ImGuiCol_WindowBg] = ImVec4(global_config.menu_background_color[0], global_config.menu_background_color[1], global_config.menu_background_color[2], global_config.menu_background_color[3]);
    colors[ImGuiCol_Header] = ImVec4(global_config.primary_color[0], global_config.primary_color[1], global_config.primary_color[2], global_config.primary_color[3]); // Primary color for headers
    colors[ImGuiCol_HeaderHovered] = ImVec4(global_config.primary_color[0] * 1.1f, global_config.primary_color[1] * 1.1f, global_config.primary_color[2] * 1.1f, global_config.primary_color[3]); // Hover color for headers
    colors[ImGuiCol_HeaderActive] = ImVec4(global_config.primary_color[0] * 1.2f, global_config.primary_color[1] * 1.2f, global_config.primary_color[2] * 1.2f, global_config.primary_color[3]); // Active color for headers
    colors[ImGuiCol_Button] = ImVec4(global_config.menu_button_color[0], global_config.menu_button_color[1], global_config.menu_button_color[2], global_config.menu_button_color[3]); // Primary color for buttons
    colors[ImGuiCol_ButtonHovered] = ImVec4(global_config.primary_color[0] * 1.1f, global_config.primary_color[1] * 1.1f, global_config.primary_color[2] * 1.1f, global_config.primary_color[3]); // Hover color for buttons
    colors[ImGuiCol_ButtonActive] = ImVec4(global_config.primary_color[0] * 1.2f, global_config.primary_color[1] * 1.2f, global_config.primary_color[2] * 1.2f, global_config.primary_color[3]); // Active color for buttons

    // Frame Background
    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f); // Dark gray
    colors[ImGuiCol_FrameBgHovered] = ImVec4(global_config.primary_color[0] * 0.2f, global_config.primary_color[1] * 0.2f, global_config.primary_color[2] * 0.2f, global_config.primary_color[3]); // Darker red on hover
    colors[ImGuiCol_FrameBgActive] = ImVec4(global_config.primary_color[0] * 1.2f, global_config.primary_color[1] * 1.2f, global_config.primary_color[2] * 1.2f, global_config.primary_color[3]); // Active color for frame background

    // Blood Neon Red for Checkboxes and Sliders
    colors[ImGuiCol_CheckMark] = ImVec4(global_config.primary_color[0], global_config.primary_color[1], global_config.primary_color[2], global_config.primary_color[3]); // Checkmark color
    colors[ImGuiCol_SliderGrab] = ImVec4(global_config.primary_color[0], global_config.primary_color[1], global_config.primary_color[2], global_config.primary_color[3]); // Slider grab color
    colors[ImGuiCol_SliderGrabActive] = ImVec4(global_config.primary_color[0] * 1.2f, global_config.primary_color[1] * 1.2f, global_config.primary_color[2] * 1.2f, global_config.primary_color[3]); // Active slider color

    // Title bar
    colors[ImGuiCol_TitleBg] = ImVec4(global_config.primary_color[0], global_config.primary_color[1], global_config.primary_color[2], global_config.primary_color[3]); // Title bar color
    colors[ImGuiCol_TitleBgActive] = ImVec4(global_config.primary_color[0] * 1.1f, global_config.primary_color[1] * 1.1f, global_config.primary_color[2] * 1.1f, global_config.primary_color[3]); // Active title bar color
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(global_config.primary_color[0] * 0.75f, global_config.primary_color[1] * 0.75f, global_config.primary_color[2] * 0.75f, global_config.primary_color[3] * 0.75f); // Collapsed title bar color

    // Miscellaneous colors
    colors[ImGuiCol_Border] = ImVec4(global_config.menu_border_color[0], global_config.menu_border_color[1], global_config.menu_border_color[2], global_config.menu_border_color[3]);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // No shadow

    // Popup background
    colors[ImGuiCol_PopupBg] = ImVec4(global_config.menu_tooltip_color[0], global_config.menu_tooltip_color[1], global_config.menu_tooltip_color[2], global_config.menu_tooltip_color[3]);

    // Additional colors
    colors[ImGuiCol_ScrollbarBg] = ImVec4(global_config.menu_scrollbar_color[0], global_config.menu_scrollbar_color[1], global_config.menu_scrollbar_color[2], global_config.menu_scrollbar_color[3]);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(global_config.menu_scrollbar_grab_color[0], global_config.menu_scrollbar_grab_color[1], global_config.menu_scrollbar_grab_color[2], global_config.menu_scrollbar_grab_color[3]);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(global_config.menu_scrollbar_grab_hovered_color[0], global_config.menu_scrollbar_grab_hovered_color[1], global_config.menu_scrollbar_grab_hovered_color[2], global_config.menu_scrollbar_grab_hovered_color[3]);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(global_config.menu_scrollbar_grab_active_color[0], global_config.menu_scrollbar_grab_active_color[1], global_config.menu_scrollbar_grab_active_color[2], global_config.menu_scrollbar_grab_active_color[3]);
    colors[ImGuiCol_TitleBg] = ImVec4(global_config.menu_title_color[0], global_config.menu_title_color[1], global_config.menu_title_color[2], global_config.menu_title_color[3]);
    colors[ImGuiCol_SliderGrab] = ImVec4(global_config.menu_slider_color[0], global_config.menu_slider_color[1], global_config.menu_slider_color[2], global_config.menu_slider_color[3]);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(global_config.menu_slider_active_color[0], global_config.menu_slider_active_color[1], global_config.menu_slider_active_color[2], global_config.menu_slider_active_color[3]);
    colors[ImGuiCol_Tab] = ImVec4(global_config.menu_tab_color[0], global_config.menu_tab_color[1], global_config.menu_tab_color[2], global_config.menu_tab_color[3]);
    colors[ImGuiCol_TabHovered] = ImVec4(global_config.menu_tab_hovered_color[0], global_config.menu_tab_hovered_color[1], global_config.menu_tab_hovered_color[2], global_config.menu_tab_hovered_color[3]);
    colors[ImGuiCol_TabActive] = ImVec4(global_config.menu_tab_active_color[0], global_config.menu_tab_active_color[1], global_config.menu_tab_active_color[2], global_config.menu_tab_active_color[3]);
    colors[ImGuiCol_CheckMark] = ImVec4(global_config.menu_checkbox_color[0], global_config.menu_checkbox_color[1], global_config.menu_checkbox_color[2], global_config.menu_checkbox_color[3]);

    colors[ImGuiCol_PlotLines] = ImVec4(global_config.menu_progress_color[0], global_config.menu_progress_color[1], global_config.menu_progress_color[2], global_config.menu_progress_color[3]);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(global_config.menu_progress_filled_color[0], global_config.menu_progress_filled_color[1], global_config.menu_progress_filled_color[2], global_config.menu_progress_filled_color[3]);

    // Styling adjustments
    style.WindowRounding = 5.0f;
    style.FrameRounding = 5.0f;
    style.GrabRounding = 5.0f;
    style.PopupRounding = 5.0f;
    style.ScrollbarRounding = 5.0f;
    style.WindowPadding = ImVec2(12.0f, 12.0f);
    style.FramePadding = ImVec2(8.0f, 6.0f);
    style.ItemSpacing = ImVec2(10.0f, 5.0f);
    style.ScrollbarSize = 16.0f;
    style.WindowBorderSize = 1.5f;
    style.FrameBorderSize = 1.5f;
}

// Function to setup GUI context
void menu::setupGui(GLFWwindow* window, const char* glsl_version) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load custom fonts
    ImFont* font = io.Fonts->AddFontFromFileTTF("path/to/your/font.ttf", 16.0f);
    if (font == nullptr) {
        std::cerr << "Failed to load font!" << std::endl;
    }
}

// Function to setup GLFW window
GLFWwindow* menu::setupGlfw(const char* window_title, int width, int height) {
    if (!glfwInit())
        return nullptr;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor) {
        glfwTerminate();
        return nullptr;
    }

    glfwWindowHint(GLFW_FLOATING, true);
    glfwWindowHint(GLFW_MAXIMIZED, true);
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, true);

    GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return nullptr;
    }

    glfwSetWindowAttrib(window, GLFW_DECORATED, false);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    return window;
}
