#pragma once
#include "datatypes.h"
#include "config.h"
#include "render.h"
#include "offsets.hpp"
#include "client_dll.hpp"
#include "buttons.hpp"
#include "proc.h"
#include "animationsystem_dll.hpp"
#include "geometry.h"
#include <mutex>
#include "main.h"
#include "proc.h"




bool GetClient(DWORD procId);
void RenderEntities();
void GetPlayer();
void Aim(Vec2& ScreenPosition);
void Aimlock(Vec2& ScreenPosition);
void LoopAimbot(Vec2& ScreenPosition);
void Fov();
void Bhop();
void Triggerbot();
void checkBombPlanted();