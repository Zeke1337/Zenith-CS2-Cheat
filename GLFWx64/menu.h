#pragma once
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "config.h"
#include "datatypes.h"
#include <Windows.h>
#include <algorithm>



namespace menu
{
	void HideMenu(GLFWwindow* Window);
	void ShowMenu(GLFWwindow* Window);

	void Render(Config& config);
	void RenderSecondaryWindow(Config& config, Client& client);

	void SetCustomBlackTheme();
	void setupGui(GLFWwindow* window, const char* glsl_version);
	GLFWwindow* setupGlfw(const char* window_title, int width, int height);

}