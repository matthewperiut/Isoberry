//
// Created by matthewperiut on 5/14/2021.
//

#pragma once

#include <vector>
#include <string>
#include "../tool/layering/DrawOrderSystem.h"
#include "../tool/Img.h"

class Level
{
public:
    olc::PixelGameEngine* engine;
private:
    int numberReserved{ 0 };
    int numberImported{ 0 };

    v3 tempPos{0,0,0};

    std::vector<Img*> images;
    std::vector<std::string*> imgpaths;
    std::vector<v3> positions;
    std::vector<Collider> colliders;
public:
    DrawOrderSystem DOS;
public:
    Level();
    Level(olc::PixelGameEngine& g) : engine( &g )
    { DOS = DrawOrderSystem(g); }
    void LoadFromFile(std::string path);
    ~Level();

    void DrawAll();
};