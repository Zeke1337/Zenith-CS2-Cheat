#pragma once

#include "datatypes.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32 // Define before including glfw3native.h
#include <GLFW/glfw3native.h>   // Include GLFW native header
#include "math.h"
#include "utilities.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "config.h"

void ShowNameInText(Vec2& FeetCoords, GLuint& fontBase, const char* name);
void DrawCornerOutline(Vec2& FeetCoords, Vec2& HeadCoords, Config& cnf);
void DrawOutline(Vec2& FeetCoords, Vec2& HeadCoords, Config& cnf);

void drawFOVCircle(float radius, const Vec2& screenCenter);

void DrawLine(Vec2& x, Vec2& y, Config& cnf);

void renderText(const char* text, GLuint listBase, float x, float y);

void DrawBox(Vec2& FeetCoords, Vec2& HeadCoords, Config& cnf);

void DrawHealthbar(Vec2& FeetCoords, Vec2& HeadCoords, Config& cnf, int health);

void DrawSnaplinesBottom(Vec2& FeetCoords, Config& cnf);

void DrawSnaplinesTop(Vec2& HeadCoords, Config& cnf);

void DrawSnaplinesCenter(Vec2& HeadCoords, Config& cnf);

void DrawHeadBox(Vec2& FeetCoords, Vec2& HeadCoords, Config& cnf);

void ShowHealthInText(Vec2& FeetCoords, GLuint& fontBase, Config& cnf, int health);


void DrawArmorbar(Vec2& FeetCoords, Vec2& HeadCoords, Config& cnf, int armor);

void drawRadarPoint(float x, float y, glm::vec3 color);

void drawRadarBackground(float radarSize);

void drawPlayerArrow(float radarSize, float playerYaw);


GLuint createBitmapFont(HDC hdc, const char* fontName, int fontHeight);

