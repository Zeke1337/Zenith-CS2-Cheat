#pragma once
#include "datatypes.h"
#include "config.h"
#include "render.h"
#include "proc.h"
#include "geometry.h"
#include <mutex>
#include "main.h"
#include "proc.h"


#include "json.hpp"
#include <fstream>
#include <unordered_map>
#include <string>
#include <iostream>


#include <sstream>
#include <iomanip>
#include "animationsystem_dll.hpp"
#include "buttons.hpp"
#include "client_dll.hpp"
#include "offsets.hpp"


bool GetClient(DWORD procId);
void RenderEntities();
void GetPlayer();
void Aim(Vec2& ScreenPosition);
void Aimlock(Vec2& ScreenPosition);
void Fov();
void NoFlash();
void Bhop();
void Triggerbot();
void checkBombPlanted();
void UpdateEntity(Entity& entity, int& playerIndex);
void LoopAimbot(Vec2& ScreenPosition);