//
// Created by matthewperiut on 10/4/21.
//

#include "Garbage.h"
#include <olcPixelGameEngine.h>

void Garbage::DeleteAll()
{
    for(int i = 0; i < sprites.size(); i++)
    {
        delete reinterpret_cast<olc::Sprite*>(sprites[i]);
    }
    for(int i = 0; i < decals.size(); i++)
    {
        delete reinterpret_cast<olc::Sprite*>(decals[i]);
    }
}

Garbage garbage;