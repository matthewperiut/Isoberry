//
// Created by matthewperiut on 5/7/21.
//

#pragma once

#include "../tool/v3.h"
#include "Object.h"

class Player : public Object
{
public:
    Player(const v3& size) : Object(size)
    {
        isPlayer = true;
        isEntity = true;
    }
    Player(const v3& size, const v3& position) : Object(size, position)
    {
        isPlayer = true;
        isEntity = true;
    }
    void KeyboardInput(olc::PixelGameEngine& g);
};
