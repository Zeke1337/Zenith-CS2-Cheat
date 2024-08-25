#pragma once

#include "datatypes.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32 // Define before including glfw3native.h
#include <GLFW/glfw3native.h>   // Include GLFW native header
#include "math.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "config.h"


GLuint createBitmapFont(HDC hdc, const char* fontName, int fontHeight);

namespace OpenGl
{
	// Function declarations

	// Function to draw a circle representing the FOV
	void DrawFOVCircle(float radius, const Vec2& screenCenter);

	// Function to render text using the bitmap font
	void RenderText(const char* text, GLuint listBase, float x, float y);

	// Function to draw an outlined box around an entity
	void DrawBox(Vec2& FeetCoords, Vec2& HeadCoords);

	// Function to draw an outline around an entity
	void DrawOutline(Vec2& FeetCoords, Vec2& HeadCoords);

	// Function to draw a cornered outline around an entity
	void DrawCornerOutline(Vec2& FeetCoords, Vec2& HeadCoords);

	// Function to draw the health bar of an entity
	void DrawHealthBar(Vec2& FeetCoords, Vec2& HeadCoords, int health);

	// Function to draw the armor bar of an entity
	void DrawArmorBar(Vec2& FeetCoords, Vec2& HeadCoords, int armor);

	// Function to draw snaplines from different screen positions
	void DrawSnaplinesBottom(Vec2& FeetCoords);
	void DrawSnaplinesTop(Vec2& HeadCoords);
	void DrawSnaplinesCenter(Vec2& HeadCoords);

	// Function to draw a line (usually for skeletons or other overlays)
	void DrawLine(Vec2& x, Vec2& y);

	// Function to convert HSV to RGB color space
	Vec3 HSVtoRGB(float h, float s, float v);

	// Function to draw a headbox around an entity's head
	void DrawHeadBox(Vec2& FeetCoords, Vec2& HeadCoords);

	// Function to display health as text on the screen
	void ShowHealthInText(Vec2& FeetCoords, GLuint& fontBase, int health);

	// Function to display a player's name as text on the screen
	void ShowNameInText(Vec2& FeetCoords, GLuint& fontBase, const char* name);

	// Function to draw a point on the radar
	void DrawRadarPoint(float x, float y, glm::vec3 color);

	// Function to draw the radar background
	void DrawRadarBackground(float radarSize);

	// Function to draw an arrow on the radar indicating the player's direction
	void DrawPlayerArrow(float radarSize, float playerYaw);
}
