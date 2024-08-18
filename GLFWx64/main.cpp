#include "main.h"

std::vector<Entity> enemies(64);

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


int Start(bool status) {
    Config cnf;
    const char* glsl_version = "#version 130";
    int width = 1920;
    int height = 1080;


    


    // Setup GLFW and create window
    GLFWwindow* window = menu::setupGlfw("", width, height);
    if (!window) return -1;

    // Setup ImGui
    menu::setupGui(window, glsl_version);

    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Get device context
    HDC hdc = GetDC(glfwGetWin32Window(window));

    // Create bitmap font
    GLuint fontBase = createBitmapFont(hdc, "Consolas", 20);

    
    DWORD procId = GetProcId(L"cs2.exe");
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);
    Client client{};
    GetClient(client, procId);
    Player player;
    Vec2 ScreenPosition = { width / 2.0f, (height / 2.0f) - 20 };

    std::thread bombCheck(checkBombPlanted, hProc, std::ref(client));
    bombCheck.detach(); // Detach the thread to run independently

    std::thread runBhop(Bhop, hProc, std::ref(player), std::ref(client));
    runBhop.detach();

    // Main loop
    while (!glfwWindowShouldClose(window) && status) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        if (GetAsyncKeyState(VK_INSERT) & 1) {
            cnf.bShowMenu = !cnf.bShowMenu;
            if (cnf.bShowMenu) {
                menu::ShowMenu(window);
            }
            else {
                menu::HideMenu(window);
            }
        }

        if (cnf.bShowMenu) {
            menu::Render(cnf);
        }

        if (cnf.bEnableFov)
        {
            Fov(hProc, player, cnf);
            iFov(hProc, player, cnf);
        }

        if (cnf.bEnableThirdperson)
        {
            ThirdPerson(hProc, player, cnf);
        }

        if (cnf.bBombTimer)
        {
            // Always render the secondary window
            
            menu::RenderSecondaryWindow(cnf,client);
        }

        if (cnf.bNoFlash)
        {
            NoFlash(hProc, player);
        }

        // Game logic here
        GetPlayer(hProc, client.baseAddress, player);
        client.entitylist = Memory::RPM<uintptr_t>(hProc, (client.baseAddress + dumper::offsets::client_dll::dwEntityList));

        // Process and draw the filtered entities
        for (int i = 1; i < enemies.size(); ++i) {
            GetEntity(hProc, client, player, enemies[i], i, cnf);

            if (enemies[i].bValid) {

                if (!ConvertTo2D(enemies[i], player))
                    continue;

                if (cnf.bEnableSkeleton)
                {
                    for (int j = 0; j < sizeof(boneConnections) / sizeof(boneConnections[0]); j++)
                    {
                        int bone1 = boneConnections[j].bone1;
                        int bone2 = boneConnections[j].bone2;

                        Vec3 VectorBones1 = Memory::RPM<Vec3>(hProc, (enemies[i].sceneNode + (bone1 * 32)));
                        Vec3 VectorBones2 = Memory::RPM<Vec3>(hProc, (enemies[i].sceneNode + (bone2 * 32)));

                        Vec2 b1;
                        Vec2 b2;
                        if (!WorldToScreenEsp(VectorBones1, b1, player.Matrix.Matrix))
                            continue;
                        if (!WorldToScreenEsp(VectorBones2, b2, player.Matrix.Matrix))
                            continue;

                        DrawLine(b1, b2, cnf);
                    }
                }
                
                

                
                if (cnf.bEnableEsp)
                {
                    switch (cnf.comboIndexEsp)
                    {
                    case 0: 
                        DrawOutline(enemies[i].FeetCoords, enemies[i].NeckCoords, cnf);
                        break;
                    case 1:
                        DrawCornerOutline(enemies[i].FeetCoords, enemies[i].NeckCoords, cnf);
                        break;
                    case 2:
                        DrawBox(enemies[i].FeetCoords, enemies[i].NeckCoords, cnf);
                        break;
                    default:
                        break;
                    }
                    
                }

                if (cnf.bEnableNameEsp) { ShowNameInText(enemies[i].NeckCoords, fontBase, enemies[i].cName); }
                if(cnf.bEnemyHealthBarEsp) { DrawHealthbar(enemies[i].FeetCoords, enemies[i].NeckCoords, cnf, enemies[i].health); }
                if(cnf.bEnemyArmorBarEsp) { DrawArmorbar(enemies[i].FeetCoords, enemies[i].NeckCoords, cnf, enemies[i].iArmor); }
                if(cnf.bHealthTextEsp) { ShowHealthInText(enemies[i].FeetCoords, fontBase, cnf, enemies[i].health); }
                if (cnf.bGameRadar) { Radar(hProc, enemies[i]); };

                if (cnf.bEnableSnaplines)
                {
                    switch (cnf.comboIndex)
                    {
                    case 0:
                        DrawSnaplinesTop(enemies[i].NeckCoords, cnf);
                        break;
                    case 1:
                        DrawSnaplinesCenter(enemies[i].NeckCoords, cnf);
                        break;
                    case 2:
                        DrawSnaplinesBottom(enemies[i].NeckCoords, cnf);
                        break;
                    default:
                        break;
                    }
                }

                
            }
        }

        
        
        


        // Correct the screen center coordinates
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);

        if (cnf.bEnableAimbot) 
        {
            Aim(hProc, client, player, enemies, ScreenPosition, cnf);

        }

        if (cnf.bEnableAimbot || cnf.bEnableAimlock)
        {
            glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
            glLineWidth(2.0f);

            // Draw the FOV circle
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0.0f, display_w, display_h, 0.0f, -1.0f, 1.0f);
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            drawFOVCircle(cnf.fFovRadius, ScreenPosition);
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }

        if (cnf.bTriggerbot) { if (GetAsyncKeyState(VK_SHIFT) & 0x8000) { Triggerbot(hProc, player, client); } };
        
        if(cnf.bEnableAimlock) 
        {
            Aimlock(hProc, client, player, enemies, ScreenPosition, cnf);
            //Triggerbot(hProc, player, client);
        }

        

        // Poll for and process events
        glfwPollEvents();

        // Rendering
        ImGui::Render();
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers
        glfwSwapBuffers(window);

        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Sleep for 30 ms (~33 updates per second)
    }

    bombCheck.join();
    runBhop.join();
    glfwTerminate();
    return 0;
}
