#pragma once
#include "datatypes.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32 // Define before including glfw3native.h
#include <GLFW/glfw3native.h>   // Include GLFW native header
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

bool WorldToScreenAimbot(const Vec3 VecOrigin, Vec2& VecScreen, const float* Matrix);
bool WorldToScreenEsp(const Vec3 VecOrigin, Vec2& VecScreen, const float* Matrix);
