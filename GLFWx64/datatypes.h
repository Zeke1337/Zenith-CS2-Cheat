#pragma once
#include <vector>
#include <chrono>

#include <cstddef>
#include <cstdint>





#define JUMP 65537
#define STANDING  65665
#define CROUCHING  65667
#define INAIR 65664
#define PLUS 65537
#define MINUS 256



struct Vec2 {
    float X;
    float Y;

    Vec2() : X(0), Y(0) {} // Default constructor
    Vec2(float x, float y) : X(x), Y(y) {} // Constructor with parameters
};


class Vec3 {
public:
    float X, Y, Z;

    Vec3() : X(0), Y(0), Z(0) {}
    Vec3(float x, float y, float z) : X(x), Y(y), Z(z) {}

    // Define the multiplication operator
    Vec3 operator*(float scalar) const {
        return Vec3(X * scalar, Y * scalar, Z * scalar);
    }

    // You might also want to define addition
    Vec3 operator+(const Vec3& other) const {
        return Vec3(X + other.X, Y + other.Y, Z + other.Z);
    }

    // Other operators can be defined similarly (like -, /, etc.)
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
    Vec3 Velocity{};
    ViewMatrix Matrix{};
    uintptr_t baseAdress;
    uintptr_t sceneNode;
    uintptr_t gamescene;
    uintptr_t camerServices;
    uintptr_t observerServices;
    Vec3 NeckOrigin;
    Vec2 NeckCoords;
    int iTeam;
    int flag;
    bool isScoped = false;
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


extern struct Player player;
extern struct Client client;
extern std::vector<Entity> enemies;






