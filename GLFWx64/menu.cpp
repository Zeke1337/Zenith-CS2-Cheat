#include "menu.h"

void menu::HideMenu(GLFWwindow* Window) {
    glfwSetWindowAttrib(Window, GLFW_MOUSE_PASSTHROUGH, true);
}

void menu::ShowMenu(GLFWwindow* Window) {
    glfwSetWindowAttrib(Window, GLFW_MOUSE_PASSTHROUGH, false);
}

// Function to convert ImGuiKey to a string for display
const char* GetKeyName(ImGuiKey key)
{
    if (key == ImGuiKey_None)
        return "None";
    return ImGui::GetKeyName(key);
}


void menu::Render(Config& config) {

    if (!config.bShowMenu)
        return;

    static int selectedTab = 0;
    // Variables to store key state and keybind
    int aimbotKey = ImGuiKey_F;  // You can use any key here
    bool aimbotActive = false;   // State to track if aimbot is active

    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(750.0f, 400.0f));

    // Begin main window with no scrollbars
    ImGui::Begin("xphax", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

    // Tabs
    ImGui::BeginChild("Tabs", ImVec2(120, 0), true, ImGuiWindowFlags_NoScrollbar); // No scrollbar in the tabs child
    if (ImGui::Button("Aimbot", ImVec2(120, 40))) {
        selectedTab = 0;
    }
    if (ImGui::Button("Visuals", ImVec2(120, 40))) {
        selectedTab = 1;
    }
    if (ImGui::Button("Misc", ImVec2(120, 40))) {
        selectedTab = 2;
    }
    if (ImGui::Button("Settings", ImVec2(120, 40))) {
        selectedTab = 3;
    }
    ImGui::EndChild();

    ImGui::SameLine();

    // Main Content
    ImGui::BeginGroup();
    ImGui::BeginChild("MainContent", ImVec2(600, 0), true, ImGuiWindowFlags_NoScrollbar); // No scrollbar in the main content child

    switch (selectedTab) {
    case 0: // Aimbot
    {
        ImGui::Text("Legit");
        ImGui::Separator();
        ImGui::Checkbox("Aimbot", &config.bEnableAimbot);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Toggle aimbot on/off");

        ImGui::Checkbox("Triggerbot", &config.bTriggerbot);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Auto shoot when target is in crosshair");

        ImGui::SliderFloat("FOV", &config.fFovRadius, 0.0f, 180.0f);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Field of View for aimbot");

        ImGui::SliderFloat("Smoothness", &config.fSmoothIndex, 1.0f, 10.0f);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Smoothness of aimbot movement");

        ImGui::Text("Rage");
        ImGui::Separator();
        ImGui::Checkbox("Aimlock", &config.bEnableAimlock);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Lock aim onto targets. Press SHIFT to toggle on");
        break;
    }
    case 1: // Visuals
    {
        ImGui::BeginChild("Esp", ImVec2(580.0f, 140.0f), true, ImGuiWindowFlags_NoScrollbar); // Adjusted child size and removed scrollbar
        ImGui::Text("Esp");
        ImGui::Separator();
        ImGui::Spacing();

        // Checkbox aligned to the left
        ImGui::Checkbox("Esp", &config.bEnableEsp);

        // Move cursor to the very right edge of the window
        ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - ImGui::CalcItemWidth());

        // Color picker aligned to the very right
        ImGui::ColorEdit4("##EspColor", config.fColorEsp, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

        ImGui::Spacing();
        ImGui::Combo("Combo Esp", &config.comboIndexEsp, config.comboItemsEsp, IM_ARRAYSIZE(config.comboItemsEsp)); // Adjusted combo box length
        ImGui::Spacing();
        ImGui::SliderFloat("Corner Line Index", &config.fLineIndex, 1.0f, 10.0f);
        ImGui::EndChild();

        ImGui::Spacing();

        ImGui::BeginChild("Snaplines", ImVec2(580.0f, 110.0f), true, ImGuiWindowFlags_NoScrollbar); // Adjusted child size and removed scrollbar
        ImGui::Text("Snaplines");
        ImGui::Separator();
        ImGui::Spacing();

        // Checkbox aligned to the left
        ImGui::Checkbox("Snaplines", &config.bEnableSnaplines);

        // Move cursor to the very right edge of the window
        ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - ImGui::CalcItemWidth());

        // Color picker aligned to the very right
        ImGui::ColorEdit4("##SnaplinesColor", config.fColorSnapline, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

        ImGui::Spacing();
        ImGui::Combo("Combo Snaplines", &config.comboIndex, config.comboItemsSnapline, IM_ARRAYSIZE(config.comboItemsSnapline)); // Adjusted combo box length
        ImGui::EndChild();

        ImGui::Spacing();

        ImGui::BeginChild("Esp Miscellaneous", ImVec2(580.0f, 200.0f), true, ImGuiWindowFlags_NoScrollbar); // Adjusted child size and removed scrollbar
        ImGui::Text("Esp Miscellaneous");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("Health Bar", &config.bEnemyHealthBarEsp);
        ImGui::Spacing();
        ImGui::Checkbox("Armor Bar", &config.bEnemyArmorBarEsp);
        ImGui::Spacing();
        ImGui::Checkbox("Health Text", &config.bHealthTextEsp);
        ImGui::Spacing();
        ImGui::Checkbox("Name Text", &config.bEnableNameEsp);
        ImGui::Spacing();
        ImGui::Checkbox("Radar", &config.bGameRadar);
        ImGui::EndChild();
        break;
    }
    case 2: // Misc
    {
        ImGui::Text("Miscellaneous");
        ImGui::Separator();
        ImGui::Checkbox("Bomb Timer", &config.bBombTimer);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Shows time until bomb explodes");

        ImGui::Checkbox("No Flash", &config.bNoFlash);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Disable flashbang effect");

        ImGui::Checkbox("Bhop", &config.bBhop);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Auto bunny hop");
        break;
    }
    case 3: // Settings
    {
        ImGui::Text("Settings");
        ImGui::Separator();
        if (ImGui::Button("Save Config")) {
            SaveConfig("MyConfig", config);
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Save your current settings");

        if (ImGui::Button("Load Config")) {
            LoadConfig("MyConfig", config);
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Load saved settings");
        break;
    }
    }

    ImGui::EndChild(); // End main content child
    ImGui::EndGroup();
    ImGui::End();

    ImGui::PopStyleVar();
}





void menu::RenderSecondaryWindow(Config& config, Client& client) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(200.f, 20.f));
    ImGui::Begin("Another Window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    
    // Calculate progress for the bomb timer
    float progress = client.iBombTickTime / 40.0f;

    // Render the progress bar for the bomb timer
    ImGui::Text("Bomb Timer");
    ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f), std::to_string(40 - client.iBombTickTime).c_str());

    ImGui::End();

}

void menu::SetCustomBlackTheme() {


    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Main background color
    colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);

    // Headers
    colors[ImGuiCol_Header] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.20f, 0.29f, 0.30f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.29f, 0.30f, 1.00f);

    // Buttons
    colors[ImGuiCol_Button] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 0.29f, 0.30f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.29f, 0.30f, 1.00f);

    // Frame Background
    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);

    // Darker Pink for Checkboxes and Sliders
    colors[ImGuiCol_CheckMark] = ImVec4(0.6f, 0.0f, 0.4f, 1.00f);  // Darker Pink
    colors[ImGuiCol_SliderGrab] = ImVec4(0.6f, 0.0f, 0.4f, 1.00f);  // Darker Pink
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.7f, 0.1f, 0.5f, 1.00f);  // Slightly lighter dark pink

    // Text
    colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);

    // Tabs (childs)
    colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

    // Border color
    colors[ImGuiCol_Border] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    // Popup background
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);

    // Darker Pink for Title bar
    colors[ImGuiCol_TitleBg] = ImVec4(0.6f, 0.0f, 0.4f, 1.00f);  // Darker Pink
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.7f, 0.1f, 0.5f, 1.00f);  // Slightly lighter dark pink
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.6f, 0.0f, 0.4f, 0.75f);  // Slightly transparent dark pink

    // Styling adjustments
    style.WindowRounding = 3.0f;
    style.FrameRounding = 3.0f;
    style.GrabRounding = 3.0f;
    style.PopupRounding = 3.0f;
    style.ScrollbarRounding = 3.0f;
    style.WindowPadding = ImVec2(10.0f, 10.0f);
    style.FramePadding = ImVec2(6.0f, 4.0f);
    style.ItemSpacing = ImVec2(8.0f, 4.0f);
    style.ScrollbarSize = 15.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    
   
    /*
    * ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.3f;
    style.FrameRounding = 2.3f;
    style.ScrollbarRounding = 0;

    style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
    #
    */
    
}

void menu::setupGui(GLFWwindow* window, const char* glsl_version) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    SetCustomBlackTheme();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

GLFWwindow* menu::setupGlfw(const char* window_title, int width, int height) {
    // Initialize the library
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
