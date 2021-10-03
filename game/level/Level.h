//
// Created by matthewperiut on 5/14/2021.
//

#pragma once

#include <vector>
#include <string>
#include "../tool/layering/DrawOrderSystem.h"
#include "../tool/Img.h"
#include "../objects/Object.h"
#include "../objects/Player.h"

class Level
{
public:
    olc::PixelGameEngine* engine;
private:
    std::vector<Object*> objects;
public:
    DrawOrderSystem DOS;
    std::string name = "";

    std::vector<Player>* playersPtr;
public:
    Level();
    Level(olc::PixelGameEngine& g) : engine( &g )
    { DOS = DrawOrderSystem(g); }
    void LoadFromFile(std::string path);
    ~Level();

    void DrawAll();
};