#include "menu.h"

void menu::HideMenu(GLFWwindow* Window) {
    glfwSetWindowAttrib(Window, GLFW_MOUSE_PASSTHROUGH, true);
}

void menu::ShowMenu(GLFWwindow* Window) {
    glfwSetWindowAttrib(Window, GLFW_MOUSE_PASSTHROUGH, false);
}

#include "menu.h"

// Function to convert ImGuiKey to a string for display
const char* GetKeyName(ImGuiKey key) {
    if (key == ImGuiKey_None)
        return "None";
    return ImGui::GetKeyName(key);
}

void menu::Render(Config& config) {
    if (!config.bShowMenu)
        return;

    static int selectedTab = 0;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(800.0f, 500.0f));
    ImGui::Begin("ZENITH", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

    

    ApplyCustomColors(config);

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
        ImGui::Checkbox("Aimbot", &config.bEnableAimbot);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Enable aimbot functionality");
            ImGui::EndTooltip();
        }
        ImGui::Checkbox("Triggerbot", &config.bTriggerbot);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Automatically shoot when aiming at an enemy");
            ImGui::EndTooltip();
        }
        ImGui::SliderFloat("FOV", &config.fFovRadius, 0.0f, 180.0f, "FOV: %.1f");
        ImGui::SliderFloat("Smoothness", &config.fSmoothIndex, 1.0f, 10.0f, "Smoothness: %.1f");
        ImGui::Text("Rage");
        ImGui::Separator();
        ImGui::Checkbox("Aimlock", &config.bEnableAimlock);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Lock your aim on the nearest enemy");
            ImGui::EndTooltip();
        }
        break;

    case 1: // Visuals
        ImGui::Text("ESP");
        ImGui::Separator();
        ImGui::Checkbox("Enable ESP", &config.bEnableEsp);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Show enemies through walls");
            ImGui::EndTooltip();
        }
        ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - ImGui::CalcItemWidth());
        ImGui::ColorEdit4("##EspColor", config.fColorEsp, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Change the color of ESP");
            ImGui::EndTooltip();
        }

        ImGui::Checkbox("Skeleton", &config.bEnableSkeleton);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Show skeletons of enemies");
            ImGui::EndTooltip();
        }
        ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - ImGui::CalcItemWidth());
        ImGui::ColorEdit4("##SkeletonColor", config.fColorSkeleton, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Change the color of skeletons");
            ImGui::EndTooltip();
        }

        ImGui::Combo("Skeleton Color Effect", &config.comboIndexSkeletonColor, config.comboItemsSkeletonColor, IM_ARRAYSIZE(config.comboItemsSkeletonColor));
        ImGui::Combo("Combo ESP", &config.comboIndexEsp, config.comboItemsEsp, IM_ARRAYSIZE(config.comboItemsEsp));
        ImGui::SliderFloat("Corner Line Index", &config.fLineIndex, 1.0f, 10.0f);

        ImGui::Separator();
        ImGui::Checkbox("Snaplines", &config.bEnableSnaplines);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Draw snaplines to enemies");
            ImGui::EndTooltip();
        }
        ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - ImGui::CalcItemWidth());
        ImGui::ColorEdit4("##SnaplinesColor", config.fColorSnapline, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Change the color of snaplines");
            ImGui::EndTooltip();
        }
        ImGui::Combo("Combo Snaplines", &config.comboIndex, config.comboItemsSnapline, IM_ARRAYSIZE(config.comboItemsSnapline)); // Adjusted combo box length
        ImGui::Separator();
        ImGui::Checkbox("Health Bar", &config.bEnemyHealthBarEsp);
        ImGui::Checkbox("Armor Bar", &config.bEnemyArmorBarEsp);
        ImGui::Checkbox("Health Text", &config.bHealthTextEsp);
        ImGui::Checkbox("Name Text", &config.bEnableNameEsp);
        ImGui::Checkbox("Radar", &config.bGameRadar);
        break;

    case 2: // Misc
        ImGui::Text("Miscellaneous");
        ImGui::Separator();
        ImGui::Checkbox("Bomb Timer", &config.bBombTimer);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Show the time remaining for the bomb");
            ImGui::EndTooltip();
        }
        ImGui::Checkbox("No Flash", &config.bNoFlash);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Prevent screen from going white from flashbangs");
            ImGui::EndTooltip();
        }
        ImGui::Checkbox("Bhop", &config.bBhop);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Enable automatic bunny hopping");
            ImGui::EndTooltip();
        }
        break;

    case 3: // Settings
        ImGui::Text("Settings");
        ImGui::Separator();

        // Save and Load Config Buttons
        if (ImGui::Button("Save Config")) {
            SaveConfig("MyConfig", config);
        }
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Save current settings to configuration file");
            ImGui::EndTooltip();
        }

        if (ImGui::Button("Load Config")) {
            LoadConfig("MyConfig", config);
        }
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Load settings from configuration file");
            ImGui::EndTooltip();
        }

        ImGui::Separator();

        // Color Customization
        ImGui::Text("Customize Menu Colors");
        ImGui::Spacing();

        ImGui::ColorEdit4("Button Color", config.menuButtonColor);
        ImGui::ColorEdit4("Button Hovered Color", config.menuButtonHoveredColor);
        ImGui::ColorEdit4("Button Active Color", config.menuButtonActiveColor);
        ImGui::ColorEdit4("Background Color", config.menuBackgroundColor);
        ImGui::ColorEdit4("Header Color", config.menuHeaderColor);
        ImGui::ColorEdit4("Menu Text Color", config.menuTextColor);
        ImGui::ColorEdit4("Menu Border Color", config.menuBorderColor);
        ImGui::ColorEdit4("Scrollbar Color", config.menuScrollbarColor);
        ImGui::ColorEdit4("Scrollbar Grab Color", config.menuScrollbarGrabColor);
        ImGui::ColorEdit4("Scrollbar Grab Hovered Color", config.menuScrollbarGrabHoveredColor);
        ImGui::ColorEdit4("Scrollbar Grab Active Color", config.menuScrollbarGrabActiveColor);
        ImGui::ColorEdit4("Title Color", config.menuTitleColor);
        ImGui::ColorEdit4("Tooltip Color", config.menuTooltipColor);
        ImGui::ColorEdit4("Tooltip Text Color", config.menuTooltipTextColor);
        ImGui::ColorEdit4("Slider Color", config.menuSliderColor);
        ImGui::ColorEdit4("Slider Hovered Color", config.menuSliderHoveredColor);
        ImGui::ColorEdit4("Slider Active Color", config.menuSliderActiveColor);
        ImGui::ColorEdit4("Tab Color", config.menuTabColor);
        ImGui::ColorEdit4("Tab Hovered Color", config.menuTabHoveredColor);
        ImGui::ColorEdit4("Tab Active Color", config.menuTabActiveColor);
        ImGui::ColorEdit4("Checkbox Color", config.menuCheckboxColor);
        ImGui::ColorEdit4("Checkbox Hovered Color", config.menuCheckboxHoveredColor);
        ImGui::ColorEdit4("Checkbox Active Color", config.menuCheckboxActiveColor);
        ImGui::ColorEdit4("Radio Color", config.menuRadioColor);
        ImGui::ColorEdit4("Radio Hovered Color", config.menuRadioHoveredColor);
        ImGui::ColorEdit4("Radio Active Color", config.menuRadioActiveColor);
        ImGui::ColorEdit4("Progress Color", config.menuProgressColor);
        ImGui::ColorEdit4("Progress Filled Color", config.menuProgressFilledColor);

        ImGui::Spacing();
        break;

    }

    ImGui::EndChild();
    ImGui::EndGroup();
    ImGui::End();

    ImGui::PopStyleVar();
}

void menu::ApplyCustomColors(Config& config) {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Apply custom colors
    colors[ImGuiCol_WindowBg] = ImVec4(config.menuBackgroundColor[0], config.menuBackgroundColor[1], config.menuBackgroundColor[2], config.menuBackgroundColor[3]);
    colors[ImGuiCol_Header] = ImVec4(config.primaryColor[0], config.primaryColor[1], config.primaryColor[2], config.primaryColor[3]); // Primary color for headers
    colors[ImGuiCol_HeaderHovered] = ImVec4(config.primaryColor[0] * 1.1f, config.primaryColor[1] * 1.1f, config.primaryColor[2] * 1.1f, config.primaryColor[3]); // Hover color for headers
    colors[ImGuiCol_HeaderActive] = ImVec4(config.primaryColor[0] * 1.2f, config.primaryColor[1] * 1.2f, config.primaryColor[2] * 1.2f, config.primaryColor[3]); // Active color for headers
    colors[ImGuiCol_Button] = ImVec4(config.menuButtonColor[0], config.menuButtonColor[1], config.menuButtonColor[2], config.menuButtonColor[3]); // Primary color for buttons
    colors[ImGuiCol_ButtonHovered] = ImVec4(config.primaryColor[0] * 1.1f, config.primaryColor[1] * 1.1f, config.primaryColor[2] * 1.1f, config.primaryColor[3]); // Hover color for buttons
    colors[ImGuiCol_ButtonActive] = ImVec4(config.primaryColor[0] * 1.2f, config.primaryColor[1] * 1.2f, config.primaryColor[2] * 1.2f, config.primaryColor[3]); // Active color for buttons

    // Frame Background
    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f); // Dark gray
    colors[ImGuiCol_FrameBgHovered] = ImVec4(config.primaryColor[0] * 0.2f, config.primaryColor[1] * 0.2f, config.primaryColor[2] * 0.2f, config.primaryColor[3]); // Darker red on hover
    colors[ImGuiCol_FrameBgActive] = ImVec4(config.primaryColor[0] * 1.2f, config.primaryColor[1] * 1.2f, config.primaryColor[2] * 1.2f, config.primaryColor[3]); // Active color for frame background

    // Blood Neon Red for Checkboxes and Sliders
    colors[ImGuiCol_CheckMark] = ImVec4(config.primaryColor[0], config.primaryColor[1], config.primaryColor[2], config.primaryColor[3]); // Checkmark color
    colors[ImGuiCol_SliderGrab] = ImVec4(config.primaryColor[0], config.primaryColor[1], config.primaryColor[2], config.primaryColor[3]); // Slider grab color
    colors[ImGuiCol_SliderGrabActive] = ImVec4(config.primaryColor[0] * 1.2f, config.primaryColor[1] * 1.2f, config.primaryColor[2] * 1.2f, config.primaryColor[3]); // Active slider color

    // Title bar
    colors[ImGuiCol_TitleBg] = ImVec4(config.primaryColor[0], config.primaryColor[1], config.primaryColor[2], config.primaryColor[3]); // Title bar color
    colors[ImGuiCol_TitleBgActive] = ImVec4(config.primaryColor[0] * 1.1f, config.primaryColor[1] * 1.1f, config.primaryColor[2] * 1.1f, config.primaryColor[3]); // Active title bar color
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(config.primaryColor[0] * 0.75f, config.primaryColor[1] * 0.75f, config.primaryColor[2] * 0.75f, config.primaryColor[3] * 0.75f); // Collapsed title bar color

    // Miscellaneous colors
    colors[ImGuiCol_Border] = ImVec4(config.menuBorderColor[0], config.menuBorderColor[1], config.menuBorderColor[2], config.menuBorderColor[3]);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // No shadow

    // Popup background
    colors[ImGuiCol_PopupBg] = ImVec4(config.menuTooltipColor[0], config.menuTooltipColor[1], config.menuTooltipColor[2], config.menuTooltipColor[3]);

    // Additional colors
    colors[ImGuiCol_ScrollbarBg] = ImVec4(config.menuScrollbarColor[0], config.menuScrollbarColor[1], config.menuScrollbarColor[2], config.menuScrollbarColor[3]);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(config.menuScrollbarGrabColor[0], config.menuScrollbarGrabColor[1], config.menuScrollbarGrabColor[2], config.menuScrollbarGrabColor[3]);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(config.menuScrollbarGrabHoveredColor[0], config.menuScrollbarGrabHoveredColor[1], config.menuScrollbarGrabHoveredColor[2], config.menuScrollbarGrabHoveredColor[3]);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(config.menuScrollbarGrabActiveColor[0], config.menuScrollbarGrabActiveColor[1], config.menuScrollbarGrabActiveColor[2], config.menuScrollbarGrabActiveColor[3]);
    colors[ImGuiCol_TitleBg] = ImVec4(config.menuTitleColor[0], config.menuTitleColor[1], config.menuTitleColor[2], config.menuTitleColor[3]);
    colors[ImGuiCol_SliderGrab] = ImVec4(config.menuSliderColor[0], config.menuSliderColor[1], config.menuSliderColor[2], config.menuSliderColor[3]);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(config.menuSliderActiveColor[0], config.menuSliderActiveColor[1], config.menuSliderActiveColor[2], config.menuSliderActiveColor[3]);
    colors[ImGuiCol_Tab] = ImVec4(config.menuTabColor[0], config.menuTabColor[1], config.menuTabColor[2], config.menuTabColor[3]);
    colors[ImGuiCol_TabHovered] = ImVec4(config.menuTabHoveredColor[0], config.menuTabHoveredColor[1], config.menuTabHoveredColor[2], config.menuTabHoveredColor[3]);
    colors[ImGuiCol_TabActive] = ImVec4(config.menuTabActiveColor[0], config.menuTabActiveColor[1], config.menuTabActiveColor[2], config.menuTabActiveColor[3]);
    colors[ImGuiCol_CheckMark] = ImVec4(config.menuCheckboxColor[0], config.menuCheckboxColor[1], config.menuCheckboxColor[2], config.menuCheckboxColor[3]);

    colors[ImGuiCol_PlotLines] = ImVec4(config.menuProgressColor[0], config.menuProgressColor[1], config.menuProgressColor[2], config.menuProgressColor[3]);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(config.menuProgressFilledColor[0], config.menuProgressFilledColor[1], config.menuProgressFilledColor[2], config.menuProgressFilledColor[3]);

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






void menu::RenderSecondaryWindow(Config& config, Client& client) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(200.f, 20.f));
    ImGui::Begin("Another Window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    float progress = client.iBombTickTime / 40.0f;

    ImGui::Text("Bomb Timer");
    ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f), std::to_string(40 - client.iBombTickTime).c_str());

    ImGui::End();
    ImGui::PopStyleVar();
}

void menu::SetCustomBlackTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Background
    colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);

    // Headers
    colors[ImGuiCol_Header] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

    // Buttons
    colors[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);

    // Frame Background
    colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

    // Checkboxes and Sliders
    colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f); // Neon red
    colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f); // Neon red
    colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.20f, 0.20f, 1.00f); // Lighter neon red

    // Text
    colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);

    // Tabs (children)
    colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

    // Borders
    colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Popup background
    colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

    // Title bar
    colors[ImGuiCol_TitleBg] = ImVec4(0.80f, 0.10f, 0.10f, 1.00f); // Neon blood red
    colors[ImGuiCol_TitleBgActive] = ImVec4(1.00f, 0.20f, 0.20f, 1.00f); // Brighter neon red
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.70f, 0.10f, 0.10f, 0.75f); // Transparent neon blood red

    // Styling adjustments
    style.WindowRounding = 5.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.WindowPadding = ImVec2(15.0f, 15.0f);
    style.FramePadding = ImVec2(8.0f, 6.0f);
    style.ItemSpacing = ImVec2(10.0f, 6.0f);
    style.ScrollbarSize = 12.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
}



void menu::setupGui(GLFWwindow* window, const char* glsl_version, Config& config) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    //ImGui::StyleColorsDark();
    //SetCustomBlackTheme();
    

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load custom fonts
    ImFont* font = io.Fonts->AddFontFromFileTTF("path/to/your/font.ttf", 16.0f);
    if (font == nullptr) {
        std::cerr << "Failed to load font!" << std::endl;
    }
}

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
