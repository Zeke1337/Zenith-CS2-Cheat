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
    }
}
