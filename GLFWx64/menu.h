#pragma once

#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "config.h"
#include "datatypes.h"
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

namespace menu
{
    // Hide the menu by making it passthrough to mouse clicks
    void HideMenu(GLFWwindow* Window);

    // Show the menu by making it interactive to mouse clicks
    void ShowMenu(GLFWwindow* Window);

    // Main render function for the menu
    void Render();
    void RenderSecondaryWindow();

    // Render additional windows or sub-menus
    //void RenderSecondaryWindow(Client& client);

    // Apply custom colors to the ImGui context based on the current configuration
    void ApplyCustomColors();

    // Set up the ImGui context and initialize it with OpenGL/GLFW
    void setupGui(GLFWwindow* window, const char* glsl_version);

    // Set up the GLFW window with specific attributes for the overlay
    GLFWwindow* setupGlfw(const char* window_title, int width, int height);

    
}

