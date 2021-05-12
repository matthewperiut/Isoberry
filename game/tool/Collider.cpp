//
// Created by matthewperiut on 5/7/21.
//

#include "../Game.h"
#include "Collider.h"
#include "DrawLineToSprite.h"
#include <cmath>

Collider::Collider(v3 size, v3 &position)
{
    this->position = &position;
    this->size = size;
}

bool Collider::isColliding(Collider &c)
{
    Collider& a = c;
    Collider& b = *this;

    //https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
    return (a.minY() <= b.maxY() && a.maxY() >= b.minY()) && a.minZ() <= b.maxZ() && a.maxZ() >= b.minZ() && a.minX() <= b.maxX() && a.maxX() >= b.minX();
}

olc::vf2d Collider::Get2dSize()
{
    olc::vf2d start;
    olc::vf2d end;
    start.x = CornerOnScreen(0,0,0).x;
    start.y = CornerOnScreen(1,0,0).y;
    end.x = CornerOnScreen(1, 0, 1).x;
    end.y = CornerOnScreen(0, 1, 1).y;

    olc::vf2d size2d = end - start;
    size2d = { std::abs(size2d.x), std::abs(size2d.y) };
    return size2d;
}

olc::Sprite* Collider::CreateSpriteDebugDraw(olc::Pixel outlineColor)
{
    olc::vf2d sprSize = Get2dSize();
    olc::Sprite* colliderSprite = new olc::Sprite(sprSize.x+1, sprSize.y+1);
    for(int i = 0; i < colliderSprite->width; i++)
    {
        for(int j = 0; j < colliderSprite->height; j++)
        {
            colliderSprite->SetPixel(i,j,olc::BLANK);
        }
    }
    for(int i = 0; i < 12; i++)
    {
        DrawLineToSprite(CornerOnScreenNormalized(box[i][0][0],box[i][0][1],box[i][0][2]),
                         CornerOnScreenNormalized(box[i][1][0],box[i][1][1],box[i][1][2]), outlineColor, *colliderSprite);

    }
    return colliderSprite;
}

void Collider::DebugDraw(olc::PixelGameEngine &game, olc::vf2d offset)
{
    //This is exclusively to update offset while drawing this frame.
    CornerOnScreen(0,0,0,&offset);

    for(int i = 0; i < 12; i++)
    {
        game.DrawLine(CornerOnScreen(box[i][0][0],box[i][0][1],box[i][0][2], &offset),
                      CornerOnScreen(box[i][1][0],box[i][1][1],box[i][1][2], &offset));
    }
}

// For the purpose of debug draw
// M for max and min, so max = 1, min = 0
olc::vf2d Collider::CornerOnScreen(bool mx, bool my, bool mz, olc::vf2d* offset)
{
    static olc::vf2d permOffset;
    v3 mpos = v3(mx ? minX() : maxX(), my ? minY() : maxY(), mz ? minZ() : maxZ());

    if(offset)
        permOffset = *offset;
    else
        return mpos.toScreen(olc::vf2d(0,0));

    return mpos.toScreen(permOffset);
}

olc::vf2d Collider::GetTopLeft(olc::vf2d offset)
{
    return olc::vf2d(
            v3(minX() , minY(), minZ()).toScreen(offset).x,
            v3(minX() , maxY(), maxZ()).toScreen(offset).y);

}

// For the purpose of drawing into a sprite
olc::vi2d Collider::CornerOnScreenNormalized(bool mx, bool my, bool mz)
{
    v3 mpos = v3(mx ? minX() : maxX(), my ? minY() : maxY(), mz ? minZ() : maxZ());
    return mpos.toScreenNoCentering();
}

float Collider::minX()
{
    return position->x;
}
float Collider::minY()
{
    return position->y;
}
float Collider::minZ()
{
    return position->z;
}
float Collider::maxX()
{
    return position->x + size.x;
}
float Collider::maxY()
{
    return position->y + size.y;
}
float Collider::maxZ()
{
    return position->z + size.z;
}