//
// Created by Matthew Periut on 9/29/21.
//

#pragma once

#include "../../level/Level.h"
#include "../../objects/Player.h"

struct ClientBundle
{
public:
    Level* level;
    Player* localPlayer;
    bool* running;
};