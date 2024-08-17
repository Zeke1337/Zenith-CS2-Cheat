#include "WorldToScreen.h"
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
