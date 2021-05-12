//
// Created by matthewperiut on 5/9/21.
//
#pragma once

#include "../../../header/olcPixelGameEngine.h"

void DrawLineToSprite(int32_t x1, int32_t y1, int32_t x2, int32_t y2, olc::Pixel p, olc::Sprite& spr, uint32_t pattern = 0xFFFFFFFF);
void DrawLineToSprite(olc::vi2d one, olc::vi2d two, olc::Pixel p, olc::Sprite& s);