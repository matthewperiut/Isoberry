//
// Created by matthewperiut on 5/9/21.
//
#include "../../../header/olcPixelGameEngine.h"

void DrawLineToSprite(int32_t x1, int32_t y1, int32_t x2, int32_t y2, olc::Pixel p, olc::Sprite& spr, uint32_t pattern)
{
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1; dy = y2 - y1;

    auto rol = [&](void) { pattern = (pattern << 1) | (pattern >> 31); return pattern & 1; };
    auto Draw = [&](int x, int y, olc::Pixel pixel) { spr.SetPixel(x,y,pixel); };

    // straight lines idea by gurkanctn
    if (dx == 0) // Line is vertical
    {
        if (y2 < y1) std::swap(y1, y2);
        for (y = y1; y <= y2; y++) if (rol()) Draw(x1, y, p);
        return;
    }

    if (dy == 0) // Line is horizontal
    {
        if (x2 < x1) std::swap(x1, x2);
        for (x = x1; x <= x2; x++) if (rol()) Draw(x, y1, p);
        return;
    }

    // Line is Funk-aye
    dx1 = abs(dx); dy1 = abs(dy);
    px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
    if (dy1 <= dx1)
    {
        if (dx >= 0)
        {
            x = x1; y = y1; xe = x2;
        }
        else
        {
            x = x2; y = y2; xe = x1;
        }

        if (rol()) Draw(x, y, p);

        for (i = 0; x < xe; i++)
        {
            x = x + 1;
            if (px < 0)
                px = px + 2 * dy1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
                px = px + 2 * (dy1 - dx1);
            }
            if (rol()) Draw(x, y, p);
        }
    }
    else
    {
        if (dy >= 0)
        {
            x = x1; y = y1; ye = y2;
        }
        else
        {
            x = x2; y = y2; ye = y1;
        }

        if (rol()) Draw(x, y, p);

        for (i = 0; y < ye; i++)
        {
            y = y + 1;
            if (py <= 0)
                py = py + 2 * dx1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
                py = py + 2 * (dx1 - dy1);
            }
            if (rol()) Draw(x, y, p);
        }
    }
}

void DrawLineToSprite(olc::vi2d one, olc::vi2d two, olc::Pixel p, olc::Sprite& s) { DrawLineToSprite(one.x,one.y,two.x,two.y,p,s, 0xFFFFFFFF); }