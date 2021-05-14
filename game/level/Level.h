//
// Created by Matthew on 5/14/2021.
//

#pragma once

#include "../tool/layering/DrawOrderSystem.h"
#include "../tool/Img.h"
#include "../Game.h"

class Level
{
public:
    olc::PixelGameEngine* game;
private:
    int numberReserved{ 0 };
    int numberImported{ 0 };

    std::vector<Img*> images;
    std::vector<v3> positions;
    std::vector<Collider> colliders;
    DrawOrderSystem DOS;
public:
    Level();
    void LoadFromFile(std::string path);
    ~Level();

    void DrawAll();
};