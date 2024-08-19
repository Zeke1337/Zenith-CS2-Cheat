#include "config.h"

using json = nlohmann::json;

void SaveConfig(const std::string& filename, Config& config) {
    json j;

    // Serialize all fields of Config
    j["bShowMenu"] = config.bShowMenu;

    j["bEnableEsp"] = config.bEnableEsp;
    j["bEnableSkeleton"] = config.bEnableSkeleton; // New variable
    j["bEnemyHealthBarEsp"] = config.bEnemyHealthBarEsp;
    j["bEnemyArmorBarEsp"] = config.bEnemyArmorBarEsp;
    j["bHealthTextEsp"] = config.bHealthTextEsp;
    j["bEnableFov"] = config.bEnableFov;

    j["bEnableSnaplines"] = config.bEnableSnaplines;
    j["bEnemySnaplines"] = config.bEnemySnaplines;
    j["bTeamSnaplines"] = config.bTeamSnaplines;

    j["bEnableAimbot"] = config.bEnableAimbot;
    j["bEnableAimlock"] = config.bEnableAimlock;

    j["bTriggerbot"] = config.bTriggerbot;

    j["bEnableRadar"] = config.bEnableRadar;
    j["bGameRadar"] = config.bGameRadar;
    j["bCustomRadar"] = config.bCustomRadar;
    j["bBombTimer"] = config.bBombTimer;
    j["bNoFlash"] = config.bNoFlash;
    j["bBhop"] = config.bBhop;
    j["bEnableBhop"] = config.bEnableBhop;
    j["bEnableNameEsp"] = config.bEnableNameEsp;

    j["comboIndex"] = config.comboIndex;
    j["comboIndexEsp"] = config.comboIndexEsp;
    j["comboIndexSkeletonColor"] = config.comboIndexSkeletonColor; // New variable
    j["fLineIndex"] = config.fLineIndex;

    // Serialize color arrays
    j["fColorEsp"] = { config.fColorEsp[0], config.fColorEsp[1], config.fColorEsp[2], config.fColorEsp[3] };
    j["fColorSkeleton"] = { config.fColorSkeleton[0], config.fColorSkeleton[1], config.fColorSkeleton[2], config.fColorSkeleton[3] }; // New variable
    j["fColorSnapline"] = { config.fColorSnapline[0], config.fColorSnapline[1], config.fColorSnapline[2], config.fColorSnapline[3] };

    j["fDistanceToHead"] = config.fDistanceToHead;
    j["fFovRadius"] = config.fFovRadius;
    j["fHitChance"] = config.fHitChance;

    j["fSmoothIndex"] = config.fSmoothIndex;

    j["iFovValue"] = config.iFovValue; // New variable
    j["bEnableThirdperson"] = config.bEnableThirdperson; // New variable

    // Serialize color settings
    j["menuButtonColor"] = { config.menuButtonColor[0], config.menuButtonColor[1], config.menuButtonColor[2], config.menuButtonColor[3] };
    j["menuButtonHoveredColor"] = { config.menuButtonHoveredColor[0], config.menuButtonHoveredColor[1], config.menuButtonHoveredColor[2], config.menuButtonHoveredColor[3] };
    j["menuButtonActiveColor"] = { config.menuButtonActiveColor[0], config.menuButtonActiveColor[1], config.menuButtonActiveColor[2], config.menuButtonActiveColor[3] };
    j["menuBackgroundColor"] = { config.menuBackgroundColor[0], config.menuBackgroundColor[1], config.menuBackgroundColor[2], config.menuBackgroundColor[3] };
    j["menuHeaderColor"] = { config.menuHeaderColor[0], config.menuHeaderColor[1], config.menuHeaderColor[2], config.menuHeaderColor[3] };

    // Serialize new color settings
    j["menuTextColor"] = { config.menuTextColor[0], config.menuTextColor[1], config.menuTextColor[2], config.menuTextColor[3] };
    j["menuBorderColor"] = { config.menuBorderColor[0], config.menuBorderColor[1], config.menuBorderColor[2], config.menuBorderColor[3] };
    j["menuScrollbarColor"] = { config.menuScrollbarColor[0], config.menuScrollbarColor[1], config.menuScrollbarColor[2], config.menuScrollbarColor[3] };
    j["menuScrollbarGrabColor"] = { config.menuScrollbarGrabColor[0], config.menuScrollbarGrabColor[1], config.menuScrollbarGrabColor[2], config.menuScrollbarGrabColor[3] };
    j["menuScrollbarGrabHoveredColor"] = { config.menuScrollbarGrabHoveredColor[0], config.menuScrollbarGrabHoveredColor[1], config.menuScrollbarGrabHoveredColor[2], config.menuScrollbarGrabHoveredColor[3] };
    j["menuScrollbarGrabActiveColor"] = { config.menuScrollbarGrabActiveColor[0], config.menuScrollbarGrabActiveColor[1], config.menuScrollbarGrabActiveColor[2], config.menuScrollbarGrabActiveColor[3] };

    j["menuTitleColor"] = { config.menuTitleColor[0], config.menuTitleColor[1], config.menuTitleColor[2], config.menuTitleColor[3] };
    j["menuTooltipColor"] = { config.menuTooltipColor[0], config.menuTooltipColor[1], config.menuTooltipColor[2], config.menuTooltipColor[3] };
    j["menuTooltipTextColor"] = { config.menuTooltipTextColor[0], config.menuTooltipTextColor[1], config.menuTooltipTextColor[2], config.menuTooltipTextColor[3] };
    j["menuSliderColor"] = { config.menuSliderColor[0], config.menuSliderColor[1], config.menuSliderColor[2], config.menuSliderColor[3] };
    j["menuSliderHoveredColor"] = { config.menuSliderHoveredColor[0], config.menuSliderHoveredColor[1], config.menuSliderHoveredColor[2], config.menuSliderHoveredColor[3] };
    j["menuSliderActiveColor"] = { config.menuSliderActiveColor[0], config.menuSliderActiveColor[1], config.menuSliderActiveColor[2], config.menuSliderActiveColor[3] };

    j["menuTabColor"] = { config.menuTabColor[0], config.menuTabColor[1], config.menuTabColor[2], config.menuTabColor[3] };
    j["menuTabHoveredColor"] = { config.menuTabHoveredColor[0], config.menuTabHoveredColor[1], config.menuTabHoveredColor[2], config.menuTabHoveredColor[3] };
    j["menuTabActiveColor"] = { config.menuTabActiveColor[0], config.menuTabActiveColor[1], config.menuTabActiveColor[2], config.menuTabActiveColor[3] };
    j["menuCheckboxColor"] = { config.menuCheckboxColor[0], config.menuCheckboxColor[1], config.menuCheckboxColor[2], config.menuCheckboxColor[3] };
    j["menuCheckboxHoveredColor"] = { config.menuCheckboxHoveredColor[0], config.menuCheckboxHoveredColor[1], config.menuCheckboxHoveredColor[2], config.menuCheckboxHoveredColor[3] };
    j["menuCheckboxActiveColor"] = { config.menuCheckboxActiveColor[0], config.menuCheckboxActiveColor[1], config.menuCheckboxActiveColor[2], config.menuCheckboxActiveColor[3] };

    j["menuRadioColor"] = { config.menuRadioColor[0], config.menuRadioColor[1], config.menuRadioColor[2], config.menuRadioColor[3] };
    j["menuRadioHoveredColor"] = { config.menuRadioHoveredColor[0], config.menuRadioHoveredColor[1], config.menuRadioHoveredColor[2], config.menuRadioHoveredColor[3] };
    j["menuRadioActiveColor"] = { config.menuRadioActiveColor[0], config.menuRadioActiveColor[1], config.menuRadioActiveColor[2], config.menuRadioActiveColor[3] };
    j["menuProgressColor"] = { config.menuProgressColor[0], config.menuProgressColor[1], config.menuProgressColor[2], config.menuProgressColor[3] };
    j["menuProgressFilledColor"] = { config.menuProgressFilledColor[0], config.menuProgressFilledColor[1], config.menuProgressFilledColor[2], config.menuProgressFilledColor[3] };


    // Save JSON to file
    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);  // 4 spaces for indentation
        file.close();
    }
}

void LoadConfig(const std::string& filename, Config& config) {
    std::ifstream file(filename);
    if (file.is_open()) {
        json j;
        file >> j;
        file.close();

        // Deserialize all fields of Config
        config.bShowMenu = j.value("bShowMenu", false);

        config.bEnableEsp = j.value("bEnableEsp", false);
        config.bEnableSkeleton = j.value("bEnableSkeleton", false); // New variable
        config.bEnemyHealthBarEsp = j.value("bEnemyHealthBarEsp", false);
        config.bEnemyArmorBarEsp = j.value("bEnemyArmorBarEsp", false);
        config.bHealthTextEsp = j.value("bHealthTextEsp", false);
        config.bEnableFov = j.value("bEnableFov", false);

        config.bEnableSnaplines = j.value("bEnableSnaplines", false);
        config.bEnemySnaplines = j.value("bEnemySnaplines", false);
        config.bTeamSnaplines = j.value("bTeamSnaplines", false);

        config.bEnableAimbot = j.value("bEnableAimbot", false);
        config.bEnableAimlock = j.value("bEnableAimlock", false);

        config.bTriggerbot = j.value("bTriggerbot", false);

        config.bEnableRadar = j.value("bEnableRadar", false);
        config.bGameRadar = j.value("bGameRadar", false);
        config.bCustomRadar = j.value("bCustomRadar", false);
        config.bBombTimer = j.value("bBombTimer", false);
        config.bNoFlash = j.value("bNoFlash", false);
        config.bBhop = j.value("bBhop", false);
        config.bEnableBhop = j.value("bEnableBhop", false);
        config.bEnableNameEsp = j.value("bEnableNameEsp", false);

        config.comboIndex = j.value("comboIndex", 0);
        config.comboIndexEsp = j.value("comboIndexEsp", 0);
        config.comboIndexSkeletonColor = j.value("comboIndexSkeletonColor", 0); // New variable
        config.fLineIndex = j.value("fLineIndex", 4.0f);

        // Deserialize color arrays
        auto colorEsp = j.value("fColorEsp", std::vector<float>{1.0f, 0.0f, 0.0f, 0.0f});
        if (colorEsp.size() == 4) {
            std::copy(colorEsp.begin(), colorEsp.end(), config.fColorEsp);
        }

        auto colorSkeleton = j.value("fColorSkeleton", std::vector<float>{1.0f, 0.0f, 0.0f, 0.0f}); // New variable
        if (colorSkeleton.size() == 4) {
            std::copy(colorSkeleton.begin(), colorSkeleton.end(), config.fColorSkeleton);
        }

        auto colorSnapline = j.value("fColorSnapline", std::vector<float>{1.0f, 0.0f, 0.0f, 0.0f});
        if (colorSnapline.size() == 4) {
            std::copy(colorSnapline.begin(), colorSnapline.end(), config.fColorSnapline);
        }

        config.fDistanceToHead = j.value("fDistanceToHead", 75.0f);
        config.fFovRadius = j.value("fFovRadius", 100.0f);
        config.fHitChance = j.value("fHitChance", 100.0f);

        config.fSmoothIndex = j.value("fSmoothIndex", 1.0f);

        config.iFovValue = j.value("iFovValue", 90); // New variable
        config.bEnableThirdperson = j.value("bEnableThirdperson", false); // New variable

        


        // Deserialize color settings
        auto buttonColor = j.value("menuButtonColor", std::vector<float>{0.10f, 0.10f, 0.10f, 1.00f});
        if (buttonColor.size() == 4) {
            std::copy(buttonColor.begin(), buttonColor.end(), config.menuButtonColor);
        }

        auto buttonHoveredColor = j.value("menuButtonHoveredColor", std::vector<float>{0.20f, 0.20f, 0.20f, 1.00f});
        if (buttonHoveredColor.size() == 4) {
            std::copy(buttonHoveredColor.begin(), buttonHoveredColor.end(), config.menuButtonHoveredColor);
        }

        auto buttonActiveColor = j.value("menuButtonActiveColor", std::vector<float>{0.30f, 0.30f, 0.30f, 1.00f});
        if (buttonActiveColor.size() == 4) {
            std::copy(buttonActiveColor.begin(), buttonActiveColor.end(), config.menuButtonActiveColor);
        }

        auto backgroundColor = j.value("menuBackgroundColor", std::vector<float>{0.05f, 0.05f, 0.05f, 1.00f});
        if (backgroundColor.size() == 4) {
            std::copy(backgroundColor.begin(), backgroundColor.end(), config.menuBackgroundColor);
        }

        auto headerColor = j.value("menuHeaderColor", std::vector<float>{0.10f, 0.10f, 0.10f, 1.00f});
        if (headerColor.size() == 4) {
            std::copy(headerColor.begin(), headerColor.end(), config.menuHeaderColor);
        }

        // Deserialize new customizable color settings
        auto menuTextColor = j.value("menuTextColor", std::vector<float>{1.00f, 1.00f, 1.00f, 1.00f});
        if (menuTextColor.size() == 4) {
            std::copy(menuTextColor.begin(), menuTextColor.end(), config.menuTextColor);
        }

        auto menuBorderColor = j.value("menuBorderColor", std::vector<float>{0.25f, 0.25f, 0.25f, 1.00f});
        if (menuBorderColor.size() == 4) {
            std::copy(menuBorderColor.begin(), menuBorderColor.end(), config.menuBorderColor);
        }

        auto menuScrollbarColor = j.value("menuScrollbarColor", std::vector<float>{0.15f, 0.15f, 0.15f, 1.00f});
        if (menuScrollbarColor.size() == 4) {
            std::copy(menuScrollbarColor.begin(), menuScrollbarColor.end(), config.menuScrollbarColor);
        }

        auto menuScrollbarGrabColor = j.value("menuScrollbarGrabColor", std::vector<float>{0.20f, 0.20f, 0.20f, 1.00f});
        if (menuScrollbarGrabColor.size() == 4) {
            std::copy(menuScrollbarGrabColor.begin(), menuScrollbarGrabColor.end(), config.menuScrollbarGrabColor);
        }

        auto menuScrollbarGrabHoveredColor = j.value("menuScrollbarGrabHoveredColor", std::vector<float>{0.30f, 0.30f, 0.30f, 1.00f});
        if (menuScrollbarGrabHoveredColor.size() == 4) {
            std::copy(menuScrollbarGrabHoveredColor.begin(), menuScrollbarGrabHoveredColor.end(), config.menuScrollbarGrabHoveredColor);
        }

        auto menuScrollbarGrabActiveColor = j.value("menuScrollbarGrabActiveColor", std::vector<float>{0.40f, 0.40f, 0.40f, 1.00f});
        if (menuScrollbarGrabActiveColor.size() == 4) {
            std::copy(menuScrollbarGrabActiveColor.begin(), menuScrollbarGrabActiveColor.end(), config.menuScrollbarGrabActiveColor);
        }

        auto menuTitleColor = j.value("menuTitleColor", std::vector<float>{0.40f, 0.40f, 0.40f, 1.00f});
        if (menuTitleColor.size() == 4) {
            std::copy(menuTitleColor.begin(), menuTitleColor.end(), config.menuTitleColor);
        }

        auto menuTooltipColor = j.value("menuTooltipColor", std::vector<float>{0.20f, 0.20f, 0.20f, 1.00f});
        if (menuTooltipColor.size() == 4) {
            std::copy(menuTooltipColor.begin(), menuTooltipColor.end(), config.menuTooltipColor);
        }

        auto menuTooltipTextColor = j.value("menuTooltipTextColor", std::vector<float>{1.00f, 1.00f, 1.00f, 1.00f});
        if (menuTooltipTextColor.size() == 4) {
            std::copy(menuTooltipTextColor.begin(), menuTooltipTextColor.end(), config.menuTooltipTextColor);
        }

        auto menuSliderColor = j.value("menuSliderColor", std::vector<float>{0.30f, 0.30f, 0.30f, 1.00f});
        if (menuSliderColor.size() == 4) {
            std::copy(menuSliderColor.begin(), menuSliderColor.end(), config.menuSliderColor);
        }

        auto menuSliderHoveredColor = j.value("menuSliderHoveredColor", std::vector<float>{0.40f, 0.40f, 0.40f, 1.00f});
        if (menuSliderHoveredColor.size() == 4) {
            std::copy(menuSliderHoveredColor.begin(), menuSliderHoveredColor.end(), config.menuSliderHoveredColor);
        }

        auto menuSliderActiveColor = j.value("menuSliderActiveColor", std::vector<float>{0.50f, 0.50f, 0.50f, 1.00f});
        if (menuSliderActiveColor.size() == 4) {
            std::copy(menuSliderActiveColor.begin(), menuSliderActiveColor.end(), config.menuSliderActiveColor);
        }

        auto menuTabColor = j.value("menuTabColor", std::vector<float>{0.15f, 0.15f, 0.15f, 1.00f});
        if (menuTabColor.size() == 4) {
            std::copy(menuTabColor.begin(), menuTabColor.end(), config.menuTabColor);
        }

        auto menuTabHoveredColor = j.value("menuTabHoveredColor", std::vector<float>{0.25f, 0.25f, 0.25f, 1.00f});
        if (menuTabHoveredColor.size() == 4) {
            std::copy(menuTabHoveredColor.begin(), menuTabHoveredColor.end(), config.menuTabHoveredColor);
        }

        auto menuTabActiveColor = j.value("menuTabActiveColor", std::vector<float>{0.35f, 0.35f, 0.35f, 1.00f});
        if (menuTabActiveColor.size() == 4) {
            std::copy(menuTabActiveColor.begin(), menuTabActiveColor.end(), config.menuTabActiveColor);
        }

        auto menuCheckboxColor = j.value("menuCheckboxColor", std::vector<float>{0.20f, 0.20f, 0.20f, 1.00f});
        if (menuCheckboxColor.size() == 4) {
            std::copy(menuCheckboxColor.begin(), menuCheckboxColor.end(), config.menuCheckboxColor);
        }

        auto menuCheckboxHoveredColor = j.value("menuCheckboxHoveredColor", std::vector<float>{0.30f, 0.30f, 0.30f, 1.00f});
        if (menuCheckboxHoveredColor.size() == 4) {
            std::copy(menuCheckboxHoveredColor.begin(), menuCheckboxHoveredColor.end(), config.menuCheckboxHoveredColor);
        }

        auto menuCheckboxActiveColor = j.value("menuCheckboxActiveColor", std::vector<float>{0.40f, 0.40f, 0.40f, 1.00f});
        if (menuCheckboxActiveColor.size() == 4) {
            std::copy(menuCheckboxActiveColor.begin(), menuCheckboxActiveColor.end(), config.menuCheckboxActiveColor);
        }

        auto menuRadioColor = j.value("menuRadioColor", std::vector<float>{0.20f, 0.20f, 0.20f, 1.00f});
        if (menuRadioColor.size() == 4) {
            std::copy(menuRadioColor.begin(), menuRadioColor.end(), config.menuRadioColor);
        }

        auto menuRadioHoveredColor = j.value("menuRadioHoveredColor", std::vector<float>{0.30f, 0.30f, 0.30f, 1.00f});
        if (menuRadioHoveredColor.size() == 4) {
            std::copy(menuRadioHoveredColor.begin(), menuRadioHoveredColor.end(), config.menuRadioHoveredColor);
        }

        auto menuRadioActiveColor = j.value("menuRadioActiveColor", std::vector<float>{0.40f, 0.40f, 0.40f, 1.00f});
        if (menuRadioActiveColor.size() == 4) {
            std::copy(menuRadioActiveColor.begin(), menuRadioActiveColor.end(), config.menuRadioActiveColor);
        }

        auto menuProgressColor = j.value("menuProgressColor", std::vector<float>{0.25f, 0.25f, 0.25f, 1.00f});
        if (menuProgressColor.size() == 4) {
            std::copy(menuProgressColor.begin(), menuProgressColor.end(), config.menuProgressColor);
        }

        auto menuProgressFilledColor = j.value("menuProgressFilledColor", std::vector<float>{0.35f, 0.35f, 0.35f, 1.00f});
        if (menuProgressFilledColor.size() == 4) {
            std::copy(menuProgressFilledColor.begin(), menuProgressFilledColor.end(), config.menuProgressFilledColor);
        }

    }
}
