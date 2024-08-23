#pragma once
#include "datatypes.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32 // Define before including glfw3native.h
#include <GLFW/glfw3native.h>   // Include GLFW native header
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "config.h"

bool WorldToScreenAimbot(const Vec3 VecOrigin, Vec2& VecScreen, const float* Matrix);
bool WorldToScreenEsp(const Vec3 VecOrigin, Vec2& VecScreen, const float* Matrix);
bool ConvertTo2D(Entity& entity);
Vec2 SmoothAngle(const Vec2& currentAngles, const Vec2& targetAngles, float smoothFactor);
void AimAtClosestEnemy(const Vec2& screenCenter, Vec2& Angles);