#include "calculations.h"

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

        float distance = calculateDistance(localPosition, enemy.NeckOrigin);

        if (distance < closestDistance) {
            closestDistance = distance;
            closestEnemyPosition = enemy.NeckOrigin;
            enemyFound = true;
        }
    }

    if (enemyFound) {
        calculateAngle(localPosition, closestEnemyPosition, angles);
    }
    else {
    }
}




