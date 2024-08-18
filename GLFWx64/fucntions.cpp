#include "functions.h"


void Aim(HANDLE& hProc, Client& client, Player& player, std::vector<Entity> enemies, Vec2& ScreenPosition, Config& cnf)
{
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
    {
        
        Vec2 Angles;
        Vec2 newAngles = Angles; // Store the original angles
        aimAtClosestEnemy(player.NeckOrigin, enemies, newAngles, ScreenPosition, cnf, player.Matrix);

        Vec2 currentAngles;
        currentAngles.X = Memory::RPM<float>(hProc, client.baseAddress + dumper::offsets::client_dll::dwViewAngles);
        currentAngles.Y = Memory::RPM<float>(hProc, client.baseAddress + dumper::offsets::client_dll::dwViewAngles+0x4);

        if (newAngles.X != Angles.X || newAngles.Y != Angles.Y) { // Check if angles were changed
            Vec2 smoothedAngles = smoothAngle(currentAngles, newAngles, cnf.fSmoothIndex); // Adjust the smooth factor as needed
            Memory::WPM<float>(hProc, client.baseAddress + dumper::offsets::client_dll::dwViewAngles, smoothedAngles.X);
            Memory::WPM<float>(hProc, client.baseAddress + dumper::offsets::client_dll::dwViewAngles+0x4, smoothedAngles.Y);
        }
    }
}


void Aimlock(HANDLE& hProc, Client& client, Player& player, std::vector<Entity>& enemies, Vec2& ScreenPosition, Config& cnf)
{
    if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
    {
        Vec2 Angles;
        Vec2 newAngles = Angles; // Store the original angles
        aimAtClosestEnemy(player.NeckOrigin, enemies, newAngles, ScreenPosition, cnf, player.Matrix);

        Vec2 currentAngles;
        currentAngles.X = Memory::RPM<float>(hProc, client.baseAddress + dumper::offsets::client_dll::dwViewAngles);
        currentAngles.Y = Memory::RPM<float>(hProc, client.baseAddress + dumper::offsets::client_dll::dwViewAngles + 0x4);

        if (newAngles.X != Angles.X || newAngles.Y != Angles.Y) { // Check if angles were changed
            Memory::WPM<float>(hProc, client.baseAddress + dumper::offsets::client_dll::dwViewAngles, newAngles.X);
            Memory::WPM<float>(hProc, client.baseAddress + dumper::offsets::client_dll::dwViewAngles + 0x4, newAngles.Y);
        }

        
    }
}




std::mutex mtx;

void checkBombPlanted(HANDLE hProc, Client& client) {
    std::lock_guard<std::mutex> lock(mtx); // Ensure that this function runs in isolation

    while (true)
    {
        uintptr_t gamerules = Memory::RPM<uintptr_t>(hProc, client.baseAddress + dumper::offsets::client_dll::dwGameRules);
        byte bombPlanted = Memory::RPM<uintptr_t>(hProc, gamerules + dumper::schemas::client_dll::C_CSGameRules::m_bBombPlanted);
        client.iBombTickTime = 0;

        if (bombPlanted) {
            for (int i = 0; i < 40; ++i) {
                bombPlanted = Memory::RPM<uintptr_t>(hProc, gamerules + dumper::schemas::client_dll::C_CSGameRules::m_bBombPlanted);
                if (!bombPlanted)
                    break;

                client.iBombTickTime++;

                Sleep(1000);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // Sleep for 30 ms (~33 updates per second)
    }
    
}

void Triggerbot(HANDLE hProc, Player& player, Client& client)
{
    uintptr_t entIndex = Memory::RPM<int>(hProc, player.baseAdress + dumper::schemas::client_dll::C_CSPlayerPawnBase::m_iIDEntIndex);

    if (entIndex != -1)
    {
        uintptr_t listentry2 = Memory::RPM<uintptr_t>(hProc, dumper::offsets::client_dll::dwEntityList + 0x8 * ((entIndex & 0x7FFF) >> 9) + 16);
        uintptr_t pCSPlayerPawn = Memory::RPM<uintptr_t>(hProc, listentry2 + 120 * (entIndex & 0x1FF));

        int entityTeam = Memory::RPM<uintptr_t>(hProc, pCSPlayerPawn + dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

        if (player.iTeam != entityTeam)
        {
            Memory::WPM<int>(hProc, client.baseAddress + dumper::buttons::attack, 65537);
            Sleep(10);
            Memory::WPM<int>(hProc, client.baseAddress + dumper::buttons::attack, 256);
            Sleep(10);
        }
    }
}

// Define flag values
const int FL_ONGROUND = (1 << 0);
void Bhop(HANDLE hProc, Player& player, Client& client)
{
    
    while (true)
    {
        int flag = Memory::RPM<int>(hProc, player.baseAdress + dumper::schemas::client_dll::C_BaseEntity::m_fFlags);

        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            if (flag & FL_ONGROUND)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Sleep for 30 ms (~33 updates per second)
                Memory::WPM<int>(hProc, client.baseAddress + dumper::buttons::jump, 65537);
            }
            else
            {
                Memory::WPM<int>(hProc, client.baseAddress + dumper::buttons::jump, 256);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Sleep for 30 ms (~33 updates per second)
    }
    
}

void NoFlash(HANDLE& hProc, Player& player)
{
    Memory::WPM<float>(hProc, (player.baseAdress + 0x1358), 0);
    Memory::WPM<float>(hProc, (player.baseAdress + 0x135C), 0);
}

void Radar(HANDLE hProc, Entity& entity)
{
    //bool spotted = Memory::RPM<bool>(hProc, entity.baseAdress + (0x2288 + 0x8));
    Memory::WPM<bool>(hProc, entity.baseAdress + (0x2288 + 0x8), 1);
}



