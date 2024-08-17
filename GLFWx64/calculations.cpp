#include "calculations.h"

const float MAX_FLOAT = 3.402823466e+38F; // Maximum value for a float

void calculateAngle(const Vec3& localPosition, const Vec3& enemyPosition, Vec2& angles) {
    Vec3 delta = { enemyPosition.X - localPosition.X, enemyPosition.Y - localPosition.Y, enemyPosition.Z - localPosition.Z };
    float hyp = sqrt(delta.X * delta.X + delta.Y * delta.Y);

    // Calculate pitch (up/down)
    angles.X = atan2(-delta.Z, hyp) * (180.0f / 3.14159265358979323846f);

    // Clamp pitch
    if (angles.X > 89.0f) angles.X = 89.0f;
    if (angles.X < -89.0f) angles.X = -89.0f;

    // Calculate yaw (left/right)
    angles.Y = atan2(delta.Y, delta.X) * (180.0f / 3.14159265358979323846f);
    
}

Vec2 smoothAngle(const Vec2& currentAngles, const Vec2& targetAngles, float smoothFactor) {
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

void aimAtClosestEnemy(const Vec3& localPosition, const std::vector<Entity>& enemies, Vec2& angles, const Vec2& screenCenter, Config& cnf, const ViewMatrix& Matrix) {
    float closestDistance = MAX_FLOAT;
    Vec3 closestEnemyPosition = { 0, 0, 0 };
    bool enemyFound = false;

    for (const auto& enemy : enemies) {
        //if (!enemy.bAlive) continue;

        if (enemy.health <= 0 || enemy.health > 100)
            continue;

        Vec2 enemyScreenPos;
        if (!WorldToScreenAimbot(enemy.NeckOrigin, enemyScreenPos, Matrix.Matrix)) {
            continue;
        }


        float screenDistance = calculateScreenDistance(enemyScreenPos, screenCenter);
        if (screenDistance > cnf.fFovRadius) {

            continue; // Skip if enemy is outside the FOV
        }

        float distance = calculateDistance(localPosition, enemy.Origin);

        if (distance < closestDistance) {
            closestDistance = distance;
            closestEnemyPosition = enemy.Origin;
            enemyFound = true;
        }
    }

    if (enemyFound) {
        calculateAngle(localPosition, closestEnemyPosition, angles);
    }
    else {
    }
}




