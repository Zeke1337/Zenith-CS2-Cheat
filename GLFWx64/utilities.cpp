#include "utilities.h"

// Helper function to convert const char* to LPCWSTR
LPCWSTR charToLPCWSTR(const char* charArray) {
    size_t len = strlen(charArray) + 1;
    wchar_t* wString = new wchar_t[len];
    size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, wString, len, charArray, _TRUNCATE);
    return wString;
}

bool GetClient(Client& client, DWORD procId)
{
	client.baseAddress = GetModuleBaseAddr(procId, L"client.dll");
    return true;
}


bool GetPlayer(HANDLE hProc,uintptr_t moduleBase,  Player& player)
{
	player.baseAdress = Memory::RPM<uintptr_t>(hProc, (moduleBase + dumper::offsets::client_dll::dwLocalPlayerPawn));
	player.Origin = Memory::RPM<Vec3>(hProc, player.baseAdress + dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin);
	player.Matrix = Memory::RPM<ViewMatrix>(hProc, (moduleBase + dumper::offsets::client_dll::dwViewMatrix));
    player.iTeam = Memory::RPM<int>(hProc, player.baseAdress + dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);
    player.gamescene = Memory::RPM<uintptr_t>(hProc, player.baseAdress + dumper::schemas::client_dll::C_BaseEntity::m_pGameSceneNode);
    player.sceneNode = Memory::RPM<uintptr_t>(hProc, player.gamescene + dumper::schemas::client_dll::CSkeletonInstance::m_modelState + dumper::schemas::animationsystem_dll::FollowAttachmentSettings_t::m_boneIndex);
    player.camerServices = Memory::RPM<uintptr_t>(hProc, (player.baseAdress + dumper::schemas::client_dll::C_BasePlayerPawn::m_pCameraServices));
    player.observerServices = Memory::RPM<uintptr_t>(hProc, (player.baseAdress + dumper::schemas::client_dll::C_BasePlayerPawn::m_pObserverServices));
    player.NeckOrigin = Memory::RPM<Vec3>(hProc, (player.sceneNode + (6 * 32)));
    uintptr_t playerController = Memory::RPM<uintptr_t>(hProc, (moduleBase + dumper::offsets::client_dll::dwLocalPlayerController));
    
    


    //Memory::ReadString(hProc, playerController + 0x630, myName, sizeof(myName));

    //std::cout << "Name: " << myName << std::endl;

    player.Angles.X = Memory::RPM<float>(hProc, moduleBase + dumper::offsets::client_dll::dwViewAngles);
    player.Angles.Y = Memory::RPM<float>(hProc, moduleBase + dumper::offsets::client_dll::dwViewAngles+0x4);
    return true;

}

void GetEntity(HANDLE hProc, Client& client, Player& player,Entity& entity,  int playerIndex, Config& cnf) {
    
    entity.bValid = false; // Initially set the entity as invalid

    uintptr_t listentry = Memory::RPM<uintptr_t>(hProc, (client.entitylist + (8 * (playerIndex & 0x7FFF) >> 9) + 16));
    if (!listentry) return ;

    uintptr_t playerController = Memory::RPM<uintptr_t>(hProc, listentry + (playerIndex*0x78));

    if (!playerController) return;
    
    Memory::ReadString(hProc, playerController + dumper::schemas::client_dll::CBasePlayerController::m_iszPlayerName, entity.cName, sizeof(entity.cName));
    

    uintptr_t playerEnt = Memory::RPM<uintptr_t>(hProc, (listentry + 120 * (playerIndex & 0x1FF)));
    if (!playerEnt) return ;

    

    int playerTeam = Memory::RPM<int>(hProc, (playerEnt + dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum));
    if (playerTeam == player.iTeam) return ;

    uint32_t playerPawn = Memory::RPM<uint32_t>(hProc, playerEnt + dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn);
    uintptr_t listentry2 = Memory::RPM<uintptr_t>(hProc, client.entitylist + 0x8 * ((playerPawn & 0x7FFF) >> 9) + 16);
    if (!listentry2) return ;

    entity.baseAdress = Memory::RPM<uintptr_t>(hProc, listentry2 + 120 * (playerPawn & 0x1FF));
    if (!entity.baseAdress) return ;
    if (entity.baseAdress == player.baseAdress) return ;

    entity.health = Memory::RPM<int>(hProc, entity.baseAdress + dumper::schemas::client_dll::C_BaseEntity::m_iHealth);
    entity.iArmor = Memory::RPM<int>(hProc, entity.baseAdress + dumper::schemas::client_dll::C_CSPlayerPawn::m_ArmorValue);
    if (entity.health <= 0 || entity.health > 100) return;

    entity.gamescene = Memory::RPM<uintptr_t>(hProc, entity.baseAdress + dumper::schemas::client_dll::C_BaseEntity::m_pGameSceneNode);
    entity.sceneNode = Memory::RPM<uintptr_t>(hProc, entity.gamescene + dumper::schemas::client_dll::CSkeletonInstance::m_modelState + dumper::schemas::animationsystem_dll::FollowAttachmentSettings_t::m_boneIndex);
    entity.Origin = Memory::RPM<Vec3>(hProc, entity.baseAdress + dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin);
    entity.headOrigin = entity.Origin;
    entity.headOrigin.Z += 75.0f;
    entity.NeckOrigin = Memory::RPM<Vec3>(hProc, (entity.sceneNode + (6 * 32)));
    
    entity.bValid = true; // Mark the entity as valid
    return ;
}


bool ConvertTo2D(Entity& entity, Player& player)
{
    if (!WorldToScreenEsp(entity.Origin, entity.FeetCoords, player.Matrix.Matrix)) return false;
    if (!WorldToScreenEsp(entity.NeckOrigin, entity.NeckCoords, player.Matrix.Matrix)) return false;
    if (!WorldToScreenEsp(entity.headOrigin, entity.HeadCoords, player.Matrix.Matrix)) return false;
    return true;
}

// Function to create bitmap display lists for a font
GLuint createBitmapFont(HDC hdc, const char* fontName, int fontHeight) {
    LPCWSTR wFontName = charToLPCWSTR(fontName); // Convert char* to LPCWSTR

    HFONT hFont = CreateFont(
        fontHeight, 0, 0, 0,
        FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_TT_PRECIS,
        CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
        FF_DONTCARE | DEFAULT_PITCH,
        wFontName);

    SelectObject(hdc, hFont);
    GLuint listBase = glGenLists(96);
    wglUseFontBitmaps(hdc, 32, 96, listBase);
    DeleteObject(hFont);
    delete[] wFontName; // Clean up the dynamically allocated memory
    return listBase;
}



