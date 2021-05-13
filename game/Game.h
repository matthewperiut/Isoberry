//
// Created by matthewperiut on 5/7/21.
//

#pragma once

#include "tool/Img.h"
#include "../header/olcPixelGameEngine.h"
#include "tool/collision/Collider.h"
#include "tool/input/ResolutionDialogue.h"
#include "tool/layering/DrawOrderSystem.h"

class Game : public olc::PixelGameEngine
{
public:
    Game();
public:
    DrawOrderSystem dos;
    ResolutionDialogue res;

    std::vector<v3> position;
    std::vector<Collider> colliders;
    olc::Sprite* boxSpr;
    olc::Decal* boxDec;

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserDestroy() override;
};

extern Game game;
