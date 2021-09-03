//
// Created by matthewperiut on 7/13/2021.
//

#include "Animation.h"

Animation::Animation(olc::Sprite& spriteSheet, olc::vi2d sectionSize, float timePerFrame)
{
    numberOfHorizontalStates = int(spriteSheet.width / sectionSize.x);
    maxNumberOfVerticalStates = int (spriteSheet.height / sectionSize.y);

    InitializeVerticalFrames();
    SetDefaultFrameThreshold(timePerFrame);

    decal = new olc::Decal(&spriteSheet);
}

Animation::~Animation()
{
    delete decal;
}

void Animation::InitializeVerticalFrames()
{
    for(int i = 0; i < numberOfHorizontalStates; i++)
    {
        verticalFrames.emplace_back(maxNumberOfVerticalStates);
    }
}

void Animation::SetDefaultFrameThreshold(float time)
{
    frameThreshold.clear();
    for(int i = 0; i < numberOfHorizontalStates; i++)
    {
        frameThreshold.emplace_back();
        for(int j = 0; j < maxNumberOfVerticalStates; j++)
        {
            frameThreshold[i].emplace_back(time);
        }
    }
}

void Animation::ChangeVerticalFrameCount(int x, int newCount)
{
    verticalFrames[x] = newCount;
}

void Animation::ChangeFrameThreshold(int x, int y, float newTime)
{
    frameThreshold[x][y] = newTime;
}

void Animation::SetDisplacement(float x, float y)
{
    displacement = olc::vf2d(x,y);
}

void Animation::SetSectionSize(float x, float y)
{
    sectionSize = olc::vf2d(x,y);
}

void Animation::SetSectionPos(float x, float y)
{
    sectionPos = olc::vf2d(x,y);
}

// Returns false if no changes are made
bool Animation::Animate(float fElapsedTime)
{
    elapsedFrame += fElapsedTime;
    if (elapsedFrame < frameThreshold[currentState][currentFrame])
        return false;

    elapsedFrame = 0;
    currentFrame++;
    if(currentFrame > verticalFrames[currentState])
        currentFrame = 0;

    return true;
}

void Animation::Draw(olc::PixelGameEngine& engine, Collider& current)
{
    engine.DrawPartialDecal(current.GetTopLeft(-displacement)+(flip*olc::vf2d(sectionSize.x,0)),
                             decal, sectionPos*sectionSize, sectionSize,
                             olc::vf2d(1 - (flip*2),1));
}



