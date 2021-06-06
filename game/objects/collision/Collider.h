//
// Created by matthewperiut on 5/7/21.
//

#pragma once

#include "../../tool/v3.h"

class Collider
{
protected:
    v3* position = nullptr;
    olc::vf2d size2d{ 0, 0 };
    v3 size{ 1, 1, 1 };
public:
    olc::Decal* dec;
public:
    Collider(v3 size, v3& position);
    bool isColliding(Collider& c);
private:
    // organization
    const static constexpr bool box[12][2][3] =
            {{{0,0,0},{1,0,0}}, //000 100
             {{0,0,0},{0,1,0}}, //000 010
             {{0,0,0},{0,0,1}}, //000 001
             {{1,0,0},{1,0,1}}, //100 101
             {{1,0,0},{1,1,0}}, //100 110
             {{1,1,0},{0,1,0}}, //110 010
             {{1,1,0},{1,1,1}}, //110 111
             {{1,1,1},{0,1,1}}, //111 011
             {{1,1,1},{1,0,1}}, //111 101
             {{0,0,1},{1,0,1}}, //001 101
             {{0,0,1},{0,1,1}}, //001 011
             {{0,1,0},{0,1,1}}};//010 011
public:
    float minX();
    float minY();
    float minZ();
    float maxX();
    float maxY();
    float maxZ();
    float minH();
    float maxH();
    float max2DY();
    float min2DY();

public:
    void SetNewPosPointer(v3& newPos);

    olc::vf2d Get2dSize();
    olc::vf2d GetTopLeft(olc::vf2d offset);
    olc::vi2d CornerOnScreenNormalized(bool mx, bool my, bool mz);
    olc::Sprite* CreateSpriteDebugDraw(olc::Pixel outlineColor = olc::WHITE);

    olc::vf2d CornerOnScreen(bool mx, bool my, bool mz, olc::vf2d *offset = nullptr);

    void DebugDraw(olc::PixelGameEngine &game, olc::vf2d offset = olc::vf2d(0,0));

    bool isAbove(Collider &a, Collider &b);
    bool isAbove(Collider &box);

    bool Overlaps(Collider &box);
};