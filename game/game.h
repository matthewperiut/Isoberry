//
// Created by matthewperiut on 5/7/21.
//

#pragma once

#include "tool/img.h"
#include "../header/olcPixelGameEngine.h"
#include "tool/collider.h"
#include "tool/input/ResolutionDialogue.h"

class Game : public olc::PixelGameEngine
{
public:
    Game();
public:
    ResolutionDialogue res;
    olc::Sprite* trying;
    olc::Decal* trdec;
    Img* test;
    v3 position = v3(0,0,0);
    v3 otherPosition = v3(0,0,0);
    Collider collider = Collider(v3(30,10,10),position);
    Collider other = Collider(v3(10,10,10),otherPosition);
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserDestroy() override;
};

extern Game game;
