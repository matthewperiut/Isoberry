//
// Created by matthewperiut on 5/7/21.
//

#pragma once

#include "tool/Img.h"
#include "../header/olcPixelGameEngine.h"
#include "objects/collision/Collider.h"
#include "tool/input/ResolutionDialogue.h"
#include "tool/layering/DrawOrderSystem.h"
#include "level/Level.h"

class Game : public olc::PixelGameEngine
{
public:
    Game();
public:
    ResolutionDialogue res;
    Level l;

    v3 shadowPosition;
    Collider* shadow;
    Img* shadowImg;

    v3 position{ -12, 1, -12 };
    Collider* collider;
    Img* img;

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserDestroy() override;
};

extern Game game;
