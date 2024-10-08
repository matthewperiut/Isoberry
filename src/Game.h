//
// Created by matthewperiut on 5/7/21.
//

#pragma once

#include "tool/Img.h"
#include <olcPixelGameEngine.h>
#include "tool/input/ResolutionDialogue.h"
#include "level/Level.h"
#include "objects/Player.h"
#include "editor/ObjectMaker.h"

class Game : public olc::PixelGameEngine
{
public:
    Game();
public:
    ObjectMaker maker;
    ResolutionDialogue res;
    Level l;

    Player test = Player(v3(8,23,8), v3(-20,1,-20), l.DOS);

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserDestroy() override;
};

extern Game game;
