#pragma once
#include "Windows.h"
#include "datatypes.h"
#include "calculations.h"
#include "config.h"
#include "proc.h"
#include "client_dll.hpp"
#include "offsets.hpp"
#include "buttons.hpp"

void Aim(HANDLE& hProc, Client& client, Player& player, std::vector<Entity> enemies, Vec2& ScreenPosition, Config& cnf);
void Aimlock(HANDLE& hProc, Client& client, Player& player, std::vector<Entity>& enemies, Vec2& ScreenPosition, Config& cnf);
void checkBombPlanted(HANDLE hProc, Client& client);
void Triggerbot(HANDLE hProc, Player& player, Client& client);
void Bhop(HANDLE hProc, Player& player, Client& client);
void NoFlash(HANDLE& hProc, Player& player);
void Radar(HANDLE hProc, Entity& entity);
void Fov(HANDLE& hProc, Player& player, Config& cnf);
void iFov(HANDLE& hProc, Player& player, Config& cnf);
void ThirdPerson(HANDLE& hProc, Player& player, Config& cnf);