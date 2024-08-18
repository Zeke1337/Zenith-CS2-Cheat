#pragma once
#include "datatypes.h"
#include "math.h"
#include <limits> // For std::numeric_limits
#include "WorldToScreen.h"
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <intrin.h>
#include <mutex>
#include <windows.h>
#include <stdio.h>
#include "config.h"
#include "draw.h"

void calculateAngle(const Vec3& localNeckPosition, const Vec3& targetNeckPosition, Vec2& angles);
Vec2 smoothAngle(const Vec2& currentAngles, const Vec2& targetAngles, float smoothFactor);
float calculateDistance(const Vec3& vecA, const Vec3& vecB);
float calculateScreenDistance(const Vec2& screenPos, const Vec2& screenCenter);
void aimAtClosestEnemy(const Vec3& localPosition, const std::vector<Entity>& enemies, Vec2& angles, const Vec2& screenCenter, Config& cnf, const ViewMatrix& matrix);

