#pragma once

#include <cstddef>
#include <cstdint>

#define JUMP 65537
#define STANDING  65665
#define CROUCHING  65667

struct Vec2 {
    float X;
    float Y;

    Vec2() : X(0), Y(0) {} // Default constructor
    Vec2(float x, float y) : X(x), Y(y) {} // Constructor with parameters
};

struct Vec3 {
    float X;
    float Y;
    float Z;
    Vec3() : X(0), Y(0), Z(0) {} // Default constructor
    Vec3(float x, float y, float z) : X(x), Y(y), Z(z) {}
};

struct Vec4 {
    float X;
    float Y;
    float Z;
    float W;
};

struct ViewMatrix {
    float Matrix[16]{};
};

struct Client {
    uintptr_t baseAddress;
    uintptr_t entitylist;
    int iBombTickTime;
};

struct Player {
    Vec2 Angles{};
    Vec3 Origin{};
    ViewMatrix Matrix{};
    uintptr_t baseAdress;
    int iTeam;
};

struct BoneConnection
{
    int bone1;
    int bone2;

    BoneConnection(int b1,int b2) : bone1(b1), bone2(b2) {};
};






struct Entity {
    int health;
    int iArmor;
    uintptr_t baseAdress;
    uintptr_t sceneNode;
    uintptr_t gamescene;
    
    Vec3 Origin;
    Vec2 HeadCoords;
    Vec2 FeetCoords;
    Vec2 NeckCoords;
    Vec3 headOrigin;
    Vec3 NeckOrigin;
    float distance;
    Vec3 Bone;
    Vec2 Bone2d;
    bool bAlive;

    int iTeam;
    bool bValid;
    char cName[16];

    


    enum BoneId : int {
        head = 6,
        neck = 5,
        spine = 4,
        spine_1 = 2,
        left_shoulder = 8,
        left_arm = 9, 
        left_hand = 16,
        cock = 0,
        right_shoulder = 13,
        right_arm = 14,
        right_hand = 16,
        left_hip = 22,
        left_knee = 23,
        left_feet = 24,
        right_hip = 25,
        right_knee = 26,
        right_feet = 27
    };


    
};
