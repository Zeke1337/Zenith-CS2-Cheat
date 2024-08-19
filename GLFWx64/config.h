#pragma once
#include <cstdint>


#include "json.hpp"
#include <iostream>
#include <fstream>
#include <string>


struct Config
{
    bool bShowMenu = false;

    bool bEnableEsp = false;
    bool bEnableSkeleton = false;
    bool bEnemyHealthBarEsp = false;
    bool bEnemyArmorBarEsp = false;
    bool bHealthTextEsp = false;
    bool bEnableFov = false;

    bool bEnableSnaplines = false;
    bool bEnemySnaplines = false;
    bool bTeamSnaplines = false;

    bool bEnableAimbot = false;
    bool bEnableAimlock = false;

    bool bTriggerbot = false;

    bool bEnableRadar = false;
    bool bGameRadar = false;
    bool bCustomRadar = false;
    bool bBombTimer = false;
    bool bNoFlash = false;
    bool bBhop = false;
    bool bEnableBhop = false;
    bool bEnableNameEsp = false;

    int comboIndex = 0;
    int comboIndexEsp = 0;
    int comboIndexSkeletonColor = 0;
    float fLineIndex = 4.0f;


    const char* comboItemsSnapline[3] = { "Top", "Center", "Bottom" };
    const char* comboItemsSkeletonColor[8] = { "Glow", "Rainbow", "Pulse", "Dynamic Color Shift", "Outer Glow", "Strobe", "Gradient", "Normal"};
    const char* comboItemsEsp[3] = { "Outline", "Corners", "Box" };

    float fColorEsp[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    float fColorSkeleton[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    float fColorSnapline[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    float fDistanceToHead = 75.0f;

    int iFovValue = 90;
    int FovValue = 90;

    bool bEnableThirdperson = false;

    float fFovRadius = 100.0f;
    float fHitChance = 100.0f;

    float fSmoothIndex = 1.0f;

    // Menu color customization
    float menuButtonColor[4] = { 0.10f, 0.10f, 0.10f, 1.00f };
    float menuButtonHoveredColor[4] = { 0.20f, 0.20f, 0.20f, 1.00f };
    float menuButtonActiveColor[4] = { 0.30f, 0.30f, 0.30f, 1.00f };
    float menuBackgroundColor[4] = { 0.05f, 0.05f, 0.05f, 1.00f };
    float menuHeaderColor[4] = { 0.10f, 0.10f, 0.10f, 1.00f };

    // Additional customizable colors
    float menuTextColor[4] = { 1.00f, 1.00f, 1.00f, 1.00f };
    float menuBorderColor[4] = { 0.25f, 0.25f, 0.25f, 1.00f };
    float menuScrollbarColor[4] = { 0.15f, 0.15f, 0.15f, 1.00f };
    float menuScrollbarGrabColor[4] = { 0.20f, 0.20f, 0.20f, 1.00f };
    float menuScrollbarGrabHoveredColor[4] = { 0.30f, 0.30f, 0.30f, 1.00f };
    float menuScrollbarGrabActiveColor[4] = { 0.40f, 0.40f, 0.40f, 1.00f };

    float menuTitleColor[4] = { 0.40f, 0.40f, 0.40f, 1.00f };
    float menuTooltipColor[4] = { 0.20f, 0.20f, 0.20f, 1.00f };
    float menuTooltipTextColor[4] = { 1.00f, 1.00f, 1.00f, 1.00f };
    float menuSliderColor[4] = { 0.30f, 0.30f, 0.30f, 1.00f };
    float menuSliderHoveredColor[4] = { 0.40f, 0.40f, 0.40f, 1.00f };
    float menuSliderActiveColor[4] = { 0.50f, 0.50f, 0.50f, 1.00f };

    float menuTabColor[4] = { 0.15f, 0.15f, 0.15f, 1.00f };
    float menuTabHoveredColor[4] = { 0.25f, 0.25f, 0.25f, 1.00f };
    float menuTabActiveColor[4] = { 0.35f, 0.35f, 0.35f, 1.00f };
    float menuCheckboxColor[4] = { 0.20f, 0.20f, 0.20f, 1.00f };
    float menuCheckboxHoveredColor[4] = { 0.30f, 0.30f, 0.30f, 1.00f };
    float menuCheckboxActiveColor[4] = { 0.40f, 0.40f, 0.40f, 1.00f };

    float menuRadioColor[4] = { 0.20f, 0.20f, 0.20f, 1.00f };
    float menuRadioHoveredColor[4] = { 0.30f, 0.30f, 0.30f, 1.00f };
    float menuRadioActiveColor[4] = { 0.40f, 0.40f, 0.40f, 1.00f };
    float menuProgressColor[4] = { 0.25f, 0.25f, 0.25f, 1.00f };
    float menuProgressFilledColor[4] = { 0.35f, 0.35f, 0.35f, 1.00f };

    // Primary color
    float primaryColor[4] = { 0.8f, 0.0f, 0.0f, 1.00f }; // Default to blood neon red



};


void SaveConfig(const std::string& filename, Config& config);
void LoadConfig(const std::string& filename, Config& config);


