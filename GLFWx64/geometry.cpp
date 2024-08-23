#include "geometry.h"
#include <iostream>

bool WorldToScreenEsp(const Vec3 VecOrigin, Vec2& VecScreen, const float* Matrix) {
    Vec4 clipCoords = {};

    clipCoords.X = VecOrigin.X * Matrix[0] + VecOrigin.Y * Matrix[1] + VecOrigin.Z * Matrix[2] + Matrix[3];
    clipCoords.Y = VecOrigin.X * Matrix[4] + VecOrigin.Y * Matrix[5] + VecOrigin.Z * Matrix[6] + Matrix[7];
    clipCoords.W = VecOrigin.X * Matrix[12] + VecOrigin.Y * Matrix[13] + VecOrigin.Z * Matrix[14] + Matrix[15];

    if (clipCoords.W < 0.1f) {
        return false;
    }

    Vec3 NDC;
    NDC.X = clipCoords.X / clipCoords.W;
    NDC.Y = clipCoords.Y / clipCoords.W;

    // Convert NDC to normalized device coordinates [-1, 1]
    VecScreen.X = NDC.X;
    VecScreen.Y = NDC.Y + 0.02f;

    return true;
}

bool WorldToScreenAimbot(const Vec3 VecOrigin, Vec2& VecScreen, const float* Matrix) {
    Vec4 clipCoords = {};

    clipCoords.X = VecOrigin.X * Matrix[0] + VecOrigin.Y * Matrix[1] + VecOrigin.Z * Matrix[2] + Matrix[3];
    clipCoords.Y = VecOrigin.X * Matrix[4] + VecOrigin.Y * Matrix[5] + VecOrigin.Z * Matrix[6] + Matrix[7];
    clipCoords.Z = VecOrigin.X * Matrix[8] + VecOrigin.Y * Matrix[9] + VecOrigin.Z * Matrix[10] + Matrix[11];
    clipCoords.W = VecOrigin.X * Matrix[12] + VecOrigin.Y * Matrix[13] + VecOrigin.Z * Matrix[14] + Matrix[15];


    if (clipCoords.W < 0.1f) {
        return false;
    }

    Vec3 NDC;
    NDC.X = clipCoords.X / clipCoords.W;
    NDC.Y = clipCoords.Y / clipCoords.W;
    NDC.Z = clipCoords.Z / clipCoords.W;


    float width = 1920;
    float height = 1080;

    // Convert NDC to screen coordinates
    VecScreen.X = (width / 2 * NDC.X) + (NDC.X + width / 2);
    VecScreen.Y = -(height / 2 * NDC.Y) + (NDC.Y + height / 2);


    return true;
}

bool ConvertTo2D(Entity& entity)
{
    if (!WorldToScreenEsp(entity.Origin, entity.FeetCoords, player.Matrix.Matrix)) return false;
    if (!WorldToScreenEsp(entity.NeckOrigin, entity.NeckCoords, player.Matrix.Matrix)) return false;
    if (!WorldToScreenEsp(entity.headOrigin, entity.HeadCoords, player.Matrix.Matrix)) return false;
    return true;
}


const float MAX_FLOAT = 3.402823466e+38F; // Maximum value for a float

// Constants
constexpr float RAD2DEG = 180.0f / 3.14159265358979323846f;

// Updated calculateAngle function
void calculateAngle(const Vec3& localNeckPosition, const Vec3& targetNeckPosition, Vec2& angles) {
    Vec3 delta = {
        targetNeckPosition.X - localNeckPosition.X,
        targetNeckPosition.Y - localNeckPosition.Y,
        targetNeckPosition.Z - localNeckPosition.Z
    };

    // Calculate the hypotenuse for the pitch (vertical) angle
    float hypotenuse = std::sqrt(delta.X * delta.X + delta.Y * delta.Y);

    // Calculate pitch (up/down angle)
    angles.X = std::atan2(-delta.Z, hypotenuse) * RAD2DEG;

    // Calculate yaw (left/right angle)
    angles.Y = std::atan2(delta.Y, delta.X) * RAD2DEG;

    // Normalize the yaw angle to be within the range of [-180, 180] degrees
    if (angles.Y < -180.0f) {
        angles.Y += 360.0f;
    }
    else if (angles.Y > 180.0f) {
        angles.Y -= 360.0f;
    }
}

Vec2 SmoothAngle(const Vec2& currentAngles, const Vec2& targetAngles, float smoothFactor) {
    Vec2 smoothedAngles;
    smoothedAngles.X = currentAngles.X + (targetAngles.X - currentAngles.X) / smoothFactor;
    smoothedAngles.Y = currentAngles.Y + (targetAngles.Y - currentAngles.Y) / smoothFactor;
    return smoothedAngles;
}

float calculateDistance(const Vec3& vecA, const Vec3& vecB) {
    return sqrt(pow(vecA.X - vecB.X, 2) + pow(vecA.Y - vecB.Y, 2) + pow(vecA.Z - vecB.Z, 2));
}

float calculateScreenDistance(const Vec2& screenPos, const Vec2& screenCenter) {
    return sqrt(pow(screenPos.X - screenCenter.X, 2) + pow(screenPos.Y - screenCenter.Y, 2));
}

void AimAtClosestEnemy(const Vec2& screenCenter, Vec2& Angles) {
    float closestDistance = MAX_FLOAT;
    Vec3 closestEnemyPosition = { 0, 0, 0 };
    bool enemyFound = false;

    for (Entity& enemy : enemies) {
        //if (!enemy.bAlive) continue;

        if (enemy.health <= 0 || enemy.health > 100)
            continue;

        if (!enemy.bValid)
            continue;

        Vec2 enemyScreenPos;

        if (!WorldToScreenAimbot(enemy.NeckOrigin, enemyScreenPos, player.Matrix.Matrix)) {
            continue;
        }


        float screenDistance = calculateScreenDistance(enemyScreenPos, screenCenter);
        if (screenDistance > global_config.fov_radius) {

            continue; // Skip if enemy is outside the FOV
        }
        else
        {
            enemyFound = true;
        }


        float distance = calculateDistance(player.NeckOrigin, enemy.NeckOrigin);

        if (distance < closestDistance) {
            closestDistance = distance;
            closestEnemyPosition = enemy.NeckOrigin;
            enemyFound = true;
        }
    }

    if (enemyFound) {
        calculateAngle(player.NeckOrigin, closestEnemyPosition, Angles);
    }
    else {
    }
}
