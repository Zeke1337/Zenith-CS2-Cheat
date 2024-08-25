#include "helper.h"

struct BoneConnection
{
    int bone1;
    int bone2;

    BoneConnection(int b1, int b2) : bone1(b1), bone2(b2) {}
};

BoneConnection boneConnections[] = {
BoneConnection(6, 5),  // head to neck
BoneConnection(5, 4),  // neck to spine
BoneConnection(4, 0),  // spine to hip
BoneConnection(4, 8), // spine to left shoulder
BoneConnection(8, 9), // left shoulder to left arm
BoneConnection(9, 11), // arm to hand
BoneConnection(4, 13),
BoneConnection(13, 14),
BoneConnection(14, 16),
BoneConnection(4, 2),  // spine to spine_1
BoneConnection(0, 22), // hip to left_hip
BoneConnection(0, 25), // hip to right_hip
BoneConnection(22, 23), // left_hip to left_knee
BoneConnection(23, 24), // left knee to left foot
BoneConnection(25, 26), // right_hip to right_knee
BoneConnection(26, 27) // right knee to right foot
};

bool GetClient(DWORD procId)
{
    client.baseAddress = GetModuleBaseAddr(procId, L"client.dll");
    return true;
}

void GetPlayer()
{
    player.baseAdress = Memory::RPM<uintptr_t>((client.baseAddress + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn));
    player.isScoped = Memory::RPM<bool>(player.baseAdress + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_bIsScoped);
    player.Origin = Memory::RPM<Vec3>(player.baseAdress + cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin);
    player.Matrix = Memory::RPM<ViewMatrix>((client.baseAddress + cs2_dumper::offsets::client_dll::dwViewMatrix));
    player.iTeam = Memory::RPM<int>(player.baseAdress + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);
    player.gamescene = Memory::RPM<uintptr_t>(player.baseAdress + cs2_dumper::schemas::client_dll::C_BaseEntity::m_pGameSceneNode);
    player.sceneNode = Memory::RPM<uintptr_t>(player.gamescene + cs2_dumper::schemas::client_dll::CSkeletonInstance::m_modelState + cs2_dumper::schemas::animationsystem_dll::FollowAttachmentSettings_t::m_boneIndex);
    player.camerServices = Memory::RPM<uintptr_t>((player.baseAdress + cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_pCameraServices));
    player.observerServices = Memory::RPM<uintptr_t>((player.baseAdress + cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_pObserverServices));
    player.NeckOrigin = Memory::RPM<Vec3>((player.sceneNode + (6 * 32)));
    uintptr_t playerController = Memory::RPM<uintptr_t>((client.baseAddress + cs2_dumper::offsets::client_dll::dwLocalPlayerController));
    player.Angles.X = Memory::RPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles);
    player.Angles.Y = Memory::RPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles + 0x4);
    player.flag = Memory::RPM<int>(player.baseAdress + cs2_dumper::schemas::client_dll::C_BaseEntity::m_fFlags);
}


void UpdateEntity(Entity& entity, int& playerIndex)
{
    entity.bValid = false;

    uintptr_t listentry = Memory::RPM<uintptr_t>((client.entitylist + (8 * (playerIndex & 0x7FFF) >> 9) + 16));
    if (!listentry) return;

    uintptr_t playerController = Memory::RPM<uintptr_t>(listentry + (playerIndex * 0x78));
    if (!playerController) return;

    Memory::ReadString(playerController + cs2_dumper::schemas::client_dll::CBasePlayerController::m_iszPlayerName, entity.cName, sizeof(entity.cName));

    uintptr_t playerEnt = Memory::RPM<uintptr_t>((listentry + 120 * (playerIndex & 0x1FF)));
    if (!playerEnt) return;

    int playerTeam = Memory::RPM<int>((playerEnt + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum));
    if (playerTeam == player.iTeam) return;

    uint32_t playerPawn = Memory::RPM<uint32_t>(playerEnt + cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn);
    uintptr_t listentry2 = Memory::RPM<uintptr_t>(client.entitylist + 0x8 * ((playerPawn & 0x7FFF) >> 9) + 16);
    if (!listentry2) return;

    entity.baseAdress = Memory::RPM<uintptr_t>(listentry2 + 120 * (playerPawn & 0x1FF));
    if (!entity.baseAdress) return;
    if (entity.baseAdress == player.baseAdress) return;

    entity.health = Memory::RPM<int>(entity.baseAdress + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth);
    entity.iArmor = Memory::RPM<int>(entity.baseAdress + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_ArmorValue);
    if (entity.health <= 0 || entity.health > 100) return;

    entity.gamescene = Memory::RPM<uintptr_t>(entity.baseAdress + cs2_dumper::schemas::client_dll::C_BaseEntity::m_pGameSceneNode);
    entity.sceneNode = Memory::RPM<uintptr_t>(entity.gamescene + cs2_dumper::schemas::client_dll::CSkeletonInstance::m_modelState + cs2_dumper::schemas::animationsystem_dll::FollowAttachmentSettings_t::m_boneIndex);
    entity.Origin = Memory::RPM<Vec3>(entity.baseAdress + cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin);
    entity.headOrigin = entity.Origin;
    entity.headOrigin.Z += 75.0f;
    entity.NeckOrigin = Memory::RPM<Vec3>((entity.sceneNode + (6 * 32)));

    entity.bValid = true;
    return;
}



void Radar(Entity& entity)
{
    Memory::WPM<bool>(entity.baseAdress + (cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_entitySpottedState + cs2_dumper::schemas::client_dll::EntitySpottedState_t::m_bSpotted), 1);
}


void RenderEntities()
{
    int i = 0;
    for (Entity& enemy : enemies) {
        UpdateEntity(enemy, i);
        if (enemy.bValid) {
            if (global_config.enable_skeleton) {
                for (int j = 0; j < sizeof(boneConnections) / sizeof(boneConnections[0]); j++) {
                    int bone1 = boneConnections[j].bone1;
                    int bone2 = boneConnections[j].bone2;

                    Vec3 VectorBones1 = Memory::RPM<Vec3>((enemy.sceneNode + (bone1 * 32)));
                    Vec3 VectorBones2 = Memory::RPM<Vec3>((enemy.sceneNode + (bone2 * 32)));

                    Vec2 b1;
                    Vec2 b2;
                    if (!WorldToScreenEsp(VectorBones1, b1, player.Matrix.Matrix))
                        continue;
                    if (!WorldToScreenEsp(VectorBones2, b2, player.Matrix.Matrix))
                        continue;

                    OpenGl::DrawLine(b1, b2);
                }
            }



            if (ConvertTo2D(enemy)) {
                if (global_config.enable_esp) {
                    switch (global_config.combo_index_esp) {
                    case 0:
                        OpenGl::DrawOutline(enemy.FeetCoords, enemy.NeckCoords);
                        break;
                    case 1:
                        OpenGl::DrawCornerOutline(enemy.FeetCoords, enemy.NeckCoords);
                        break;
                    case 2:
                        OpenGl::DrawBox(enemy.FeetCoords, enemy.NeckCoords);
                        break;
                    default:
                        break;
                    }
                }

                if (global_config.enable_name_esp) { OpenGl::ShowNameInText(enemy.NeckCoords, fontBase, enemy.cName); }
                if (global_config.enemy_health_bar_esp) { OpenGl::DrawHealthBar(enemy.FeetCoords, enemy.NeckCoords, enemy.health); }
                if (global_config.enemy_armor_bar_esp) { OpenGl::DrawArmorBar(enemy.FeetCoords, enemy.NeckCoords, enemy.iArmor); }
                if (global_config.health_text_esp) { OpenGl::ShowHealthInText(enemy.FeetCoords, fontBase, enemy.health); }
                if (global_config.enable_radar) { Radar(enemy); };

                if (global_config.enable_snaplines) {
                    switch (global_config.combo_index) {
                    case 0:
                        OpenGl::DrawSnaplinesTop(enemy.NeckCoords);
                        break;
                    case 1:
                        OpenGl::DrawSnaplinesCenter(enemy.NeckCoords);
                        break;
                    case 2:
                        OpenGl::DrawSnaplinesBottom(enemy.FeetCoords);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        ++i;
    }
}

void Aim(Vec2& ScreenPosition)
{
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
        Vec2 Angles;
        Vec2 newAngles = Angles; // Store the original angles
        AimAtClosestEnemy(ScreenPosition, newAngles);

        Vec2 currentAngles;
        currentAngles.X = Memory::RPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles);
        currentAngles.Y = Memory::RPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles + 0x4);

        if (newAngles.X != Angles.X || newAngles.Y != Angles.Y) { // Check if angles were changed
            Vec2 smoothedAngles = SmoothAngle(currentAngles, newAngles, global_config.smooth_index); // Adjust the smooth factor as needed
            Memory::WPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles, smoothedAngles.X);
            Memory::WPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles + 0x4, smoothedAngles.Y);
        }
    }
}

void Aimlock(Vec2& ScreenPosition)
{
    if (GetAsyncKeyState(VK_MENU) & 0x8000) {
        Vec2 Angles;
        Vec2 newAngles = Angles; // Store the original angles
        AimAtClosestEnemy(ScreenPosition, newAngles);

        Vec2 currentAngles;
        currentAngles.X = Memory::RPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles);
        currentAngles.Y = Memory::RPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles + 0x4);

        if (newAngles.X != Angles.X || newAngles.Y != Angles.Y) { // Check if angles were changed
            Memory::WPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles, newAngles.X);
            Memory::WPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles + 0x4, newAngles.Y);
        }
    }
}

void LoopAimbot(Vec2& ScreenPosition)
{
    if (global_config.enable_aimlock) {
        Aimlock(ScreenPosition);
    }

    if (global_config.enable_aimbot) {
        Aim(ScreenPosition);
    }
}



void NoFlash()
{
    Memory::WPM<float>((player.baseAdress + 0x1358), 0);
    Memory::WPM<float>((player.baseAdress + 0x135C), 0);
}

void SetThreadPriorityLow()
{
    auto handle = GetCurrentThread();
    SetThreadPriority(handle, THREAD_PRIORITY_LOWEST);
}

void Fov()
{
    while (true) {
        if (!player.isScoped && global_config.enable_fov) {
            Memory::WPM<uint32_t>(player.camerServices + cs2_dumper::schemas::client_dll::CCSPlayerBase_CameraServices::m_iFOVStart, global_config.fov_value);
            Memory::WPM<uint32_t>(player.camerServices + cs2_dumper::schemas::client_dll::CCSPlayerBase_CameraServices::m_iFOV, global_config.fov_value);
        }

        std::this_thread::yield(); // Allow other threads/processes to execute

        if (global_config.enable_slow_fov) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        }
    }
}

// Define flag values
const int FL_ONGROUND = (1 << 0);

void Bhop()
{
    while (true) {
        if (global_config.enable_bhop) {


            if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                if (player.flag & FL_ONGROUND) {
                    std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
                    Memory::WPM<int>(client.baseAddress + cs2_dumper::buttons::jump, 65537);
                }
                else {
                    Memory::WPM<int>(client.baseAddress + cs2_dumper::buttons::jump, 256);
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
}

void Triggerbot()
{
    while (true) {
        if (global_config.triggerbot) {
            uintptr_t entIndex = Memory::RPM<int>(player.baseAdress + cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_iIDEntIndex);

            if (entIndex != -1) {
                uintptr_t listentry2 = Memory::RPM<uintptr_t>(cs2_dumper::offsets::client_dll::dwEntityList + 0x8 * ((entIndex & 0x7FFF) >> 9) + 16);
                uintptr_t pCSPlayerPawn = Memory::RPM<uintptr_t>(listentry2 + 120 * (entIndex & 0x1FF));

                int entityTeam = Memory::RPM<uintptr_t>(pCSPlayerPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

                if (player.iTeam != entityTeam) {
                    Memory::WPM<int>(client.baseAddress + cs2_dumper::buttons::attack, 65537);
                    Sleep(100);
                    Memory::WPM<int>(client.baseAddress + cs2_dumper::buttons::attack, 256);
                    Sleep(100);
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
}

//std::mutex mtx;

void checkBombPlanted() {
    //std::lock_guard<std::mutex> lock(mtx); // Ensure that this function runs in isolation

    while (true) {
        uintptr_t gamerules = Memory::RPM<uintptr_t>(client.baseAddress + cs2_dumper::offsets::client_dll::dwGameRules);
        byte bombPlanted = Memory::RPM<uintptr_t>(gamerules + cs2_dumper::schemas::client_dll::C_CSGameRules::m_bBombPlanted);
        client.iBombTickTime = 0;

        if (bombPlanted) {
            for (int i = 0; i < 40; ++i) {
                bombPlanted = Memory::RPM<uintptr_t>(gamerules + cs2_dumper::schemas::client_dll::C_CSGameRules::m_bBombPlanted);
                if (!bombPlanted)
                    break;

                client.iBombTickTime++;
                Sleep(1000);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // Sleep for 30 ms (~33 updates per second)
    }
}
