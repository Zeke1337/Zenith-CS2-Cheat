#include "helper.h"  // Include the header file "helper.h" which contains necessary declarations and definitions.

/*
Summary of what the code does:

    Bone Connection Management: Defines how different parts of a player's skeleton are connected, useful for rendering bones (skeletons) on screen.

    Player Information Retrieval: Functions like GetPlayer retrieve and store various attributes about the local player from the game's memory.

    Entity Update and Management: Functions like UpdateEntity update information about other players or entities in the game. This includes their health, team, position, etc.

    Rendering and Visualization: RenderEntities handles the visual representation of enemies on the screen, including drawing skeletons, health bars, and other ESP (Extra Sensory Perception) features.

    Aiming and Aimbot: Aim, Aimlock, and LoopAimbot provide functionality to assist the player in aiming, automatically aiming at enemies when certain keys are pressed.

    Miscellaneous Features:
        NoFlash removes the effect of flashbang grenades.
        SetThreadPriorityLow reduces the priority of the current thread.
        Fov modifies the player's field of view (FOV).
        Bhop enables bunny hopping.
        Triggerbot automates shooting when an enemy is within the crosshair.
        checkBombPlanted monitors whether a bomb has been planted in the game.

*/



// Structure to define a connection between two bones.
struct BoneConnection {
    int bone1;  // Index of the first bone in the connection.
    int bone2;  // Index of the second bone in the connection.

    // Constructor to initialize the bone connection.
    BoneConnection(int b1, int b2) : bone1(b1), bone2(b2) {}
};

// Array of BoneConnection objects that define the connections between bones.
// Each connection defines a pair of bones that are connected.
BoneConnection boneConnections[] = {
    BoneConnection(6, 5),  // Connection between head and neck.
    BoneConnection(5, 4),  // Connection between neck and spine.
    BoneConnection(4, 0),  // Connection between spine and hip.
    BoneConnection(4, 8),  // Connection between spine and left shoulder.
    BoneConnection(8, 9),  // Connection between left shoulder and left arm.
    BoneConnection(9, 11), // Connection between left arm and hand.
    BoneConnection(4, 13), // Additional connections (context-specific).
    BoneConnection(13, 14),
    BoneConnection(14, 16),
    BoneConnection(4, 2),  // Connection between spine and another point on the spine.
    BoneConnection(0, 22), // Connection between hip and left hip.
    BoneConnection(0, 25), // Connection between hip and right hip.
    BoneConnection(22, 23), // Connection between left hip and left knee.
    BoneConnection(23, 24), // Connection between left knee and left foot.
    BoneConnection(25, 26), // Connection between right hip and right knee.
    BoneConnection(26, 27)  // Connection between right knee and right foot.
};

// Function to get the base address of the client module by its process ID.
bool GetClient(DWORD procId) {
    // Retrieve and store the base address of the "client.dll" module for the given process ID.
    client.baseAddress = GetModuleBaseAddr(procId, L"client.dll");
    return true;
}

// Function to retrieve and store information about the local player.
void GetPlayer() {
    // Read the base address of the local player pawn.
    player.baseAdress = Memory::RPM<uintptr_t>(client.baseAddress + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);

    // Read various properties of the player from memory.
    player.isScoped = Memory::RPM<bool>(player.baseAdress + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_bIsScoped);
    player.Origin = Memory::RPM<Vec3>(player.baseAdress + cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin);
    player.Matrix = Memory::RPM<ViewMatrix>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewMatrix);
    player.iTeam = Memory::RPM<int>(player.baseAdress + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);
    player.gamescene = Memory::RPM<uintptr_t>(player.baseAdress + cs2_dumper::schemas::client_dll::C_BaseEntity::m_pGameSceneNode);
    player.sceneNode = Memory::RPM<uintptr_t>(player.gamescene + cs2_dumper::schemas::client_dll::CSkeletonInstance::m_modelState + cs2_dumper::schemas::animationsystem_dll::FollowAttachmentSettings_t::m_boneIndex);
    player.camerServices = Memory::RPM<uintptr_t>(player.baseAdress + cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_pCameraServices);
    player.observerServices = Memory::RPM<uintptr_t>(player.baseAdress + cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_pObserverServices);

    // Read the position of the player's neck.
    player.NeckOrigin = Memory::RPM<Vec3>(player.sceneNode + (6 * 32));

    // Read the view angles and other properties related to the player's state.
    uintptr_t playerController = Memory::RPM<uintptr_t>(client.baseAddress + cs2_dumper::offsets::client_dll::dwLocalPlayerController);
    player.Angles.X = Memory::RPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles);
    player.Angles.Y = Memory::RPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles + 0x4);
    player.flag = Memory::RPM<int>(player.baseAdress + cs2_dumper::schemas::client_dll::C_BaseEntity::m_fFlags);
}

// Function to update information about a specific entity in the game.
void UpdateEntity(Entity& entity, int& playerIndex) {
    entity.bValid = false; // Start by marking the entity as invalid.

    // Read the list entry for the entity based on the player index.
    uintptr_t listentry = Memory::RPM<uintptr_t>(client.entitylist + (8 * (playerIndex & 0x7FFF) >> 9) + 16);
    if (!listentry) return; // If the list entry is invalid, return.

    // Read the player controller from the list entry.
    uintptr_t playerController = Memory::RPM<uintptr_t>(listentry + (playerIndex * 0x78));
    if (!playerController) return; // If the player controller is invalid, return.

    // Read the player's name from memory.
    Memory::ReadString(playerController + cs2_dumper::schemas::client_dll::CBasePlayerController::m_iszPlayerName, entity.cName, sizeof(entity.cName));

    // Read the player entity from memory.
    uintptr_t playerEnt = Memory::RPM<uintptr_t>(listentry + 120 * (playerIndex & 0x1FF));
    if (!playerEnt) return; // If the player entity is invalid, return.

    // Check if the player's team matches the local player's team.
    int playerTeam = Memory::RPM<int>(playerEnt + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);
    if (playerTeam == player.iTeam) return; // If the player is on the same team, return.

    // Read the player's pawn from memory.
    uint32_t playerPawn = Memory::RPM<uint32_t>(playerEnt + cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn);
    uintptr_t listentry2 = Memory::RPM<uintptr_t>(client.entitylist + 0x8 * ((playerPawn & 0x7FFF) >> 9) + 16);
    if (!listentry2) return; // If the second list entry is invalid, return.

    // Read the base address of the entity.
    entity.baseAdress = Memory::RPM<uintptr_t>(listentry2 + 120 * (playerPawn & 0x1FF));
    if (!entity.baseAdress) return; // If the base address is invalid, return.
    if (entity.baseAdress == player.baseAdress) return; // If the entity is the local player, return.

    // Read the health and armor of the entity.
    entity.health = Memory::RPM<int>(entity.baseAdress + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth);
    entity.iArmor = Memory::RPM<int>(entity.baseAdress + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_ArmorValue);
    if (entity.health <= 0 || entity.health > 100) return; // If the health is invalid, return.

    // Read the game scene and scene node of the entity.
    entity.gamescene = Memory::RPM<uintptr_t>(entity.baseAdress + cs2_dumper::schemas::client_dll::C_BaseEntity::m_pGameSceneNode);
    entity.sceneNode = Memory::RPM<uintptr_t>(entity.gamescene + cs2_dumper::schemas::client_dll::CSkeletonInstance::m_modelState + cs2_dumper::schemas::animationsystem_dll::FollowAttachmentSettings_t::m_boneIndex);
    entity.Origin = Memory::RPM<Vec3>(entity.baseAdress + cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin);

    // Set the head origin of the entity based on its origin and offset it upwards.
    entity.headOrigin = entity.Origin;
    entity.headOrigin.Z += 75.0f;

    // Read the position of the entity's neck.
    entity.NeckOrigin = Memory::RPM<Vec3>(entity.sceneNode + (6 * 32));

    // Mark the entity as valid.
    entity.bValid = true;
    return;
}

// Function to mark an entity as spotted on the radar.
void Radar(Entity& entity) {
    // Write to memory to mark the entity as spotted.
    Memory::WPM<bool>(entity.baseAdress + (cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_entitySpottedState + cs2_dumper::schemas::client_dll::EntitySpottedState_t::m_bSpotted), 1);
}

// Function to render entities on the screen.
void RenderEntities() {
    int i = 0; // Initialize the entity index.

    client.entitylist = Memory::RPM<uintptr_t>((client.baseAddress + cs2_dumper::offsets::client_dll::dwEntityList));

    // Iterate over all enemies in the list.
    for (Entity& enemy : enemies) {
        UpdateEntity(enemy, i); // Update the entity's information.

        if (enemy.bValid) { // If the entity is valid:

            if (global_config.enable_skeleton) { // If skeleton rendering is enabled:

                // Iterate over all bone connections.
                for (int j = 0; j < sizeof(boneConnections) / sizeof(boneConnections[0]); j++) {
                    int bone1 = boneConnections[j].bone1; // Get the first bone index.
                    int bone2 = boneConnections[j].bone2; // Get the second bone index.

                    // Read the position of both bones from memory.
                    Vec3 VectorBones1 = Memory::RPM<Vec3>(enemy.sceneNode + (bone1 * 32));
                    Vec3 VectorBones2 = Memory::RPM<Vec3>(enemy.sceneNode + (bone2 * 32));

                    Vec2 b1; // Screen position of the first bone.
                    Vec2 b2; // Screen position of the second bone.

                    // Convert the world position of the bones to screen position.
                    if (!WorldToScreenEsp(VectorBones1, b1, player.Matrix.Matrix))
                        continue; // If conversion fails, continue to the next bone connection.
                    if (!WorldToScreenEsp(VectorBones2, b2, player.Matrix.Matrix))
                        continue; // If conversion fails, continue to the next bone connection.

                    // Draw a line between the two bones on the screen.
                    OpenGl::DrawLine(b1, b2);
                }
            }

            // If converting the entity to 2D screen coordinates succeeds:
            if (ConvertTo2D(enemy)) {

                if (global_config.enable_esp) { // If ESP (Extra Sensory Perception) is enabled:
                    switch (global_config.combo_index_esp) {
                    case 0:
                        OpenGl::DrawOutline(enemy.FeetCoords, enemy.NeckCoords); // Draw a simple outline.
                        break;
                    case 1:
                        OpenGl::DrawCornerOutline(enemy.FeetCoords, enemy.NeckCoords); // Draw a corner outline.
                        break;
                    case 2:
                        OpenGl::DrawBox(enemy.FeetCoords, enemy.NeckCoords); // Draw a box around the entity.
                        break;
                    default:
                        break;
                    }
                }

                // Additional rendering options for name, health, and armor bars.
                if (global_config.enable_name_esp) {
                    OpenGl::ShowNameInText(enemy.NeckCoords, fontBase, enemy.cName); // Render the name of the entity.
                }
                if (global_config.enemy_health_bar_esp) {
                    OpenGl::DrawHealthBar(enemy.FeetCoords, enemy.NeckCoords, enemy.health); // Render the health bar.
                }
                if (global_config.enemy_armor_bar_esp) {
                    OpenGl::DrawArmorBar(enemy.FeetCoords, enemy.NeckCoords, enemy.iArmor); // Render the armor bar.
                }
                if (global_config.health_text_esp) {
                    OpenGl::ShowHealthInText(enemy.FeetCoords, fontBase, enemy.health); // Render the health text.
                }
                if (global_config.enable_radar) {
                    Radar(enemy); // Mark the entity on the radar.
                }

                // If snaplines are enabled, draw lines from the screen edges to the entity.
                if (global_config.enable_snaplines) {
                    switch (global_config.combo_index) {
                    case 0:
                        OpenGl::DrawSnaplinesTop(enemy.NeckCoords); // Draw snapline from the top.
                        break;
                    case 1:
                        OpenGl::DrawSnaplinesCenter(enemy.NeckCoords); // Draw snapline from the center.
                        break;
                    case 2:
                        OpenGl::DrawSnaplinesBottom(enemy.FeetCoords); // Draw snapline from the bottom.
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        ++i; // Increment the entity index.
    }
}

// Function to handle aiming at enemies when the left mouse button is pressed.
void Aim(Vec2& ScreenPosition) {
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // If the left mouse button is pressed:
        Vec2 Angles; // Initialize a vector to store the angles.
        Vec2 newAngles = Angles; // Store the original angles in newAngles.
        AimAtClosestEnemy(ScreenPosition, newAngles); // Adjust newAngles to aim at the closest enemy.

        Vec2 currentAngles;
        currentAngles.X = Memory::RPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles); // Read current X view angle.
        currentAngles.Y = Memory::RPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles + 0x4); // Read current Y view angle.

        // If the new angles differ from the original angles:
        if (newAngles.X != Angles.X || newAngles.Y != Angles.Y) {
            Vec2 smoothedAngles = SmoothAngle(currentAngles, newAngles, global_config.smooth_index); // Smooth the transition to the new angles.
            Memory::WPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles, smoothedAngles.X); // Write the smoothed X angle.
            Memory::WPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles + 0x4, smoothedAngles.Y); // Write the smoothed Y angle.
        }
    }
}

// Function to handle aimlock when the ALT key is pressed.
void Aimlock(Vec2& ScreenPosition) {
    if (GetAsyncKeyState(VK_MENU) & 0x8000) { // If the ALT key is pressed:
        Vec2 Angles; // Initialize a vector to store the angles.
        Vec2 newAngles = Angles; // Store the original angles in newAngles.
        AimAtClosestEnemy(ScreenPosition, newAngles); // Adjust newAngles to aim at the closest enemy.

        Vec2 currentAngles;
        currentAngles.X = Memory::RPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles); // Read current X view angle.
        currentAngles.Y = Memory::RPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles + 0x4); // Read current Y view angle.

        // If the new angles differ from the original angles:
        if (newAngles.X != Angles.X || newAngles.Y != Angles.Y) {
            Memory::WPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles, newAngles.X); // Write the new X angle.
            Memory::WPM<float>(client.baseAddress + cs2_dumper::offsets::client_dll::dwViewAngles + 0x4, newAngles.Y); // Write the new Y angle.
        }
    }
}

// Function to manage the aimbot loop, handling aimlock and aimbot.
void LoopAimbot(Vec2& ScreenPosition) {
    if (global_config.enable_aimlock) {
        Aimlock(ScreenPosition); // Call Aimlock if aimlock is enabled.
    }

    if (global_config.enable_aimbot) {
        Aim(ScreenPosition); // Call Aim if aimbot is enabled.
    }
}

// Function to prevent the player's screen from being affected by flashes (e.g., flashbangs).
void NoFlash() {
    // Write 0 to the memory addresses responsible for flash duration and intensity.
    Memory::WPM<float>(player.baseAdress + 0x1358, 0);
    Memory::WPM<float>(player.baseAdress + 0x135C, 0);
}

// Function to set the current thread's priority to the lowest level.
void SetThreadPriorityLow() {
    auto handle = GetCurrentThread(); // Get the handle of the current thread.
    SetThreadPriority(handle, THREAD_PRIORITY_LOWEST); // Set the thread priority to the lowest.
}

// Function to adjust the player's field of view (FOV) dynamically.
void Fov() {
    while (true) {
        if (!player.isScoped && global_config.enable_fov) { // If FOV adjustment is enabled and the player is not scoped:
            // Write the desired FOV value to the player's camera services.
            Memory::WPM<uint32_t>(player.camerServices + cs2_dumper::schemas::client_dll::CCSPlayerBase_CameraServices::m_iFOVStart, global_config.fov_value);
            Memory::WPM<uint32_t>(player.camerServices + cs2_dumper::schemas::client_dll::CCSPlayerBase_CameraServices::m_iFOV, global_config.fov_value);
        }

        std::this_thread::sleep_for(std::chrono::nanoseconds(1)); // Sleep for 1 nanosecond if slow FOV is enabled.
        
        std::this_thread::yield(); // Yield the thread to allow other threads/processes to execute.
    }
}

// Define flag values for various player states.
const int FL_ONGROUND = (1 << 0); // Flag indicating the player is on the ground.

// Function to handle bunny hopping (BHOP).
void Bhop() {
    while (true) {
        if (global_config.enable_bhop) { // If bunny hopping is enabled:

            if (GetAsyncKeyState(VK_SPACE) & 0x8000) { // If the space bar is pressed:
                if (player.flag & FL_ONGROUND) { // If the player is on the ground:
                    std::this_thread::sleep_for(std::chrono::nanoseconds(1000)); // Sleep for 1 microsecond.
                    Memory::WPM<int>(client.baseAddress + cs2_dumper::buttons::jump, 65537); // Perform a jump.
                }
                else {
                    Memory::WPM<int>(client.baseAddress + cs2_dumper::buttons::jump, 256); // Otherwise, write a different value to maintain the jump.
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::nanoseconds(1)); // Sleep for 1 nanosecond between checks.
    }
}

// Function to handle triggerbot functionality, automatically shooting when an enemy is in the crosshair.
void Triggerbot() {
    while (true) {
        if (global_config.triggerbot) { // If triggerbot is enabled:
            uintptr_t entIndex = Memory::RPM<int>(player.baseAdress + cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_iIDEntIndex); // Read the entity index.

            if (entIndex != -1) { // If a valid entity is targeted:
                // Read the entity from the entity list.
                uintptr_t listentry2 = Memory::RPM<uintptr_t>(cs2_dumper::offsets::client_dll::dwEntityList + 0x8 * ((entIndex & 0x7FFF) >> 9) + 16);
                uintptr_t pCSPlayerPawn = Memory::RPM<uintptr_t>(listentry2 + 120 * (entIndex & 0x1FF));

                // Read the team of the targeted entity.
                int entityTeam = Memory::RPM<uintptr_t>(pCSPlayerPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

                if (player.iTeam != entityTeam) { // If the entity is on an opposing team:
                    Memory::WPM<int>(client.baseAddress + cs2_dumper::buttons::attack, 65537); // Trigger the attack.
                    Sleep(100); // Sleep for 100 milliseconds.
                    Memory::WPM<int>(client.baseAddress + cs2_dumper::buttons::attack, 256); // Stop the attack.
                    Sleep(100); // Sleep for another 100 milliseconds.
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::nanoseconds(1)); // Sleep for 1 nanosecond between checks.
    }
}

// Function to monitor whether the bomb has been planted in the game.
void checkBombPlanted() {
    // std::lock_guard<std::mutex> lock(mtx); // Optional: Lock the function to prevent concurrent access.

    while (true) {
        // Read the game rules pointer from memory.
        uintptr_t gamerules = Memory::RPM<uintptr_t>(client.baseAddress + cs2_dumper::offsets::client_dll::dwGameRules);
        // Read the bomb planted status from memory.
        byte bombPlanted = Memory::RPM<uintptr_t>(gamerules + cs2_dumper::schemas::client_dll::C_CSGameRules::m_bBombPlanted);
        client.iBombTickTime = 0; // Reset the bomb tick time.

        if (bombPlanted) { // If the bomb is planted:
            for (int i = 0; i < 40; ++i) { // Monitor the bomb for 40 seconds.
                bombPlanted = Memory::RPM<uintptr_t>(gamerules + cs2_dumper::schemas::client_dll::C_CSGameRules::m_bBombPlanted); // Check if the bomb is still planted.
                if (!bombPlanted)
                    break; // If the bomb is defused, exit the loop.

                client.iBombTickTime++; // Increment the bomb tick time.
                Sleep(1000); // Sleep for 1 second.
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // Sleep for 30 milliseconds (~33 updates per second).
    }
}
