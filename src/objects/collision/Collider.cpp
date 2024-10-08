//
// Created by matthewperiut on 5/7/21.
//

#include "../../Game.h"
#include "Collider.h"
#include "../../tool/draw_sprites/DrawLineToSprite.h"
#include <cmath>

Collider::Collider(v3 size, v3 &position)
{
    this->positionPtr = &position;
    this->size = size;
    Get2dSize();
}

void Collider::SetNewPosPointer(v3 &newPos)
{
    this->positionPtr = &newPos;
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

    size2d = end - start;
    size2d = { std::abs(size2d.x), std::abs(size2d.y) };
    return size2d;
}

olc::Sprite* Collider::CreateSpriteDebugDraw(olc::Pixel outlineColor)
{
    olc::vf2d sprSize = Get2dSize();
    auto* colliderSprite = new olc::Sprite(sprSize.x+1, sprSize.y+1);
    for(int i = 0; i < colliderSprite->width; i++)
    {
        for(int j = 0; j < colliderSprite->height; j++)
        {
            colliderSprite->SetPixel(i,j,olc::BLANK);
        }
    }

    // Temporary fix for strange negative behavior in CornerOnScreenNormalized()
    olc::vi2d adjustment = olc::vi2d(0,CornerOnScreenNormalized(box[0][1][0],box[0][1][1],box[0][1][2]).y);

    for(int i = 0; i < 12; i++)
    {
        DrawLineToSprite(CornerOnScreenNormalized(box[i][0][0],box[i][0][1],box[i][0][2]) - adjustment,
                         CornerOnScreenNormalized(box[i][1][0],box[i][1][1],box[i][1][2]) - adjustment, outlineColor, *colliderSprite);

    }
    return colliderSprite;
}

olc::Sprite* Collider::CreateFlatShadow(olc::Pixel fillColor)
{
    int tempY = size.y;
    size.y = 1;
    olc::vf2d sprSize = Get2dSize();
    size.y = tempY;

    auto* shadowSprite = new olc::Sprite(sprSize.x+1, sprSize.y+1);
    for(int i = 0; i < shadowSprite->width; i++)
    {
        for(int j = 0; j < shadowSprite->height; j++)
        {
            shadowSprite->SetPixel(i,j,olc::BLANK);
        }
    }

    olc::Pixel grey(128,128,128,128);

    // Temporary fix for strange negative behavior in CornerOnScreenNormalized()
    olc::vi2d adjustment = olc::vi2d(0,CornerOnScreenNormalized(box[0][1][0],box[0][1][1],box[0][1][2]).y+1);

    DrawLineToSprite(CornerOnScreenNormalized(box[5][0][0],box[5][0][1],box[5][0][2]) + adjustment,
                     CornerOnScreenNormalized(box[5][1][0],box[5][1][1],box[5][1][2]) + adjustment, fillColor, *shadowSprite);
    DrawLineToSprite(CornerOnScreenNormalized(box[6][0][0],box[6][0][1],box[6][0][2]) + adjustment,
                     CornerOnScreenNormalized(box[6][1][0],box[6][1][1],box[6][1][2]) + adjustment, fillColor, *shadowSprite);
    DrawLineToSprite(CornerOnScreenNormalized(box[7][0][0],box[7][0][1],box[7][0][2]) + adjustment,
                     CornerOnScreenNormalized(box[7][1][0],box[7][1][1],box[7][1][2]) + adjustment, fillColor, *shadowSprite);
    DrawLineToSprite(CornerOnScreenNormalized(box[11][0][0],box[11][0][1],box[11][0][2]) + adjustment,
                     CornerOnScreenNormalized(box[11][1][0],box[11][1][1],box[11][1][2]) + adjustment, fillColor, *shadowSprite);

    for(int y = 0; y < shadowSprite->height; y++)
    {
        int minX = -1;
        int maxX = -1;
        for(int x = 0; x < shadowSprite->width; x++)
        {
            bool isPixel = shadowSprite->GetPixel(x,y) == fillColor;
            if(isPixel)
            {
                if(minX == -1)
                    minX = x;
                maxX = x;
                if(y==4)
                {
                    std::cout << "(" << x << "," << y << ") min: " << minX << " max: " << maxX << "\n";
                }
            }
        }
        if(minX != maxX)
            DrawLineToSprite(olc::vf2d(minX,y), olc::vf2d(maxX,y), fillColor, *shadowSprite);
    }

    return shadowSprite;
}

void Collider::DebugDraw(olc::PixelGameEngine &game, olc::vf2d offset)
{
    //This is exclusively to update offset while drawing this state.
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

v3 &Collider::GetSizeRef()
{
    return size;
}

v3 &Collider::GetPositionRef()
{
    return *positionPtr;
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
    v3 holder = *positionPtr;
    positionPtr->x = 0;
    positionPtr->y = 0;
    positionPtr->z = 0;
    v3 mpos = v3(mx ? minX() : maxX(), my ? minY() : maxY(), mz ? minZ() : maxZ());
    positionPtr->x = holder.x;
    positionPtr->y = holder.y;
    positionPtr->z = holder.z;
    return mpos.toScreenNoCentering();
}

float Collider::minX()
{
    return positionPtr->x;
}
float Collider::minY()
{
    return positionPtr->y;
}
float Collider::minZ()
{
    return positionPtr->z;
}
float Collider::maxX()
{
    return positionPtr->x + size.x;
}
float Collider::maxY()
{
    return positionPtr->y + size.y;
}
float Collider::maxZ()
{
    return positionPtr->z + size.z;
}

float Collider::min2DY() {
    return CornerOnScreen(1,0,0).y-1;
}

float Collider::max2DY() {
    return CornerOnScreen(0,1,1).y+1;
}

float Collider::minH() {
    return CornerOnScreen(1,0,1).x-1;
}

float Collider::maxH() {
    return CornerOnScreen(0,0,0).x+1;
}

bool Collider::Overlaps(Collider &box)
{
    return minH() < box.maxH() &&
           maxH() > box.minH() &&
           min2DY() < box.max2DY() &&
           max2DY() > box.min2DY();
}

bool Collider::isAbove(Collider &box) {

    return isAbove(*this, box);
}

bool Collider::isAbove(Collider &a, Collider &b)
{
    // test for intersection x-axis
    // (lower x value is in front)
    if (a.minX() >= b.maxX()) { return true; }
    else if (b.minX() >= a.maxX()) { return false; }

    // test for intersection y-axis
    // (lower y value is in front)
    if (a.minY() >= b.maxY()) { return true; }
    else if (b.minY() >= a.maxY()) { return false; }

    // test for intersection z-axis
    // (higher z value is in front)
    if (a.minZ() >= b.maxZ()) { return false; }
    else if (b.minZ() >= a.maxZ()) { return true; }

    return true;
}
