#pragma once
#include "Windows.h"
#include "datatypes.h"
#include "proc.h"
#include "client_dll.hpp"
#include "offsets.hpp"
#include "WorldToScreen.h"
#include "config.h"


LPCWSTR charToLPCWSTR(const char* charArray);
bool GetClient(Client& client, DWORD procId);
bool GetPlayer(HANDLE hProc, uintptr_t moduleBase, Player& player);
void GetEntity(HANDLE hProc, Client& client, Player& player, Entity& entity, int playerIndex, Config& cnf);
bool ConvertTo2D(Entity& entity, Player& player);