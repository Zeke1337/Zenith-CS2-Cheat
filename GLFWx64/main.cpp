#include "main.h"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>
#include <thread>
#include <windows.h>
#include <mutex>

// Global variables
HDC hdc;
GLuint fontBase;

std::mutex dataMutex;

void AimbotLoop(Vec2& ScreenPosition) {
    while (true) {
        GetPlayer();
        LoopAimbot(ScreenPosition);
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
}

int Start() {

    

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Get the primary monitor
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    if (!primaryMonitor) {
        std::cerr << "Failed to get primary monitor" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Get the current video mode of the primary monitor
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    if (!videoMode) {
        std::cerr << "Failed to get video mode" << std::endl;
        glfwTerminate();
        return -1;
    }

    int width = videoMode->width;
    int height = videoMode->height;

    DWORD procId = GetProcId(L"cs2.exe");
    hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);
    GetClient(procId);
    Vec2 ScreenPosition = { width / 2.0f, (height / 2.0f) - 20 };

    // Setup GLFW and create window
    GLFWwindow* window = menu::setupGlfw("", width, height);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Setup ImGui
    const char* glsl_version = "#version 130";
    menu::setupGui(window, glsl_version);

    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Get device context
    hdc = GetDC(glfwGetWin32Window(window));

    // Create bitmap font
    fontBase = createBitmapFont(hdc, "Consolas", 20);

    // Launch threads
    std::thread aimbotThread([&ScreenPosition] { AimbotLoop(ScreenPosition); });
    std::thread bhop([] { Bhop(); });
    std::thread runfov([] { Fov(); });
    std::thread runBomb([] { checkBombPlanted(); });
    std::thread triggerbot([] { Triggerbot(); });

    aimbotThread.detach();
    bhop.detach();
    runfov.detach();
    runBomb.detach();
    triggerbot.detach();
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        client.entitylist = Memory::RPM<uintptr_t>((client.baseAddress + cs2_dumper::offsets::client_dll::dwEntityList));
        RenderEntities();

        if (GetAsyncKeyState(VK_INSERT) & 1) {
            global_config.show_menu = !global_config.show_menu;
            if (global_config.show_menu) {
                menu::ShowMenu(window);
            }
            else {
                menu::HideMenu(window);
            }
        }

        if (global_config.show_menu) {
            menu::Render();
        }

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);

        if (global_config.enable_aimbot || global_config.enable_aimlock) {
            glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
            glLineWidth(2.0f);

            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0.0f, display_w, display_h, 0.0f, -1.0f, 1.0f);
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            OpenGl::DrawFOVCircle(global_config.fov_radius, ScreenPosition);
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }

        if (global_config.bomb_timer) {
            menu::RenderSecondaryWindow();
        }

        if (global_config.no_flash) {
            NoFlash();
        }

        glfwPollEvents();

        ImGui::Render();
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
    }

    glfwTerminate();
    return 0;
}
