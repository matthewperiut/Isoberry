//
// Created by matthewperiut on 5/7/21.
//

#pragma once

#include "tool/Img.h"
#include "../header/olcPixelGameEngine.h"
#include "objects/Collision/Collider.h"
#include "tool/input/ResolutionDialogue.h"
#include "tool/layering/DrawOrderSystem.h"
#include "level/Level.h"

class Game : public olc::PixelGameEngine
{
public:
    Game();
public:
    ResolutionDialogue res;

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserDestroy() override;
};

extern Game game;
