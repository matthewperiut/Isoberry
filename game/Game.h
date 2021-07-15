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
#include "objects/Object.h"
#include "objects/Player.h"

class Game : public olc::PixelGameEngine
{
public:
    Game();
public:
    ResolutionDialogue res;
    Level l;

    Player test = Player(v3(8,23,8), v3(-20,1,-20), l.DOS);

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserDestroy() override;
};

extern Game game;
