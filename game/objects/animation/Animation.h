//
// Created by matthewperiut on 7/13/2021.
//

#pragma once

#include "../../../header/olcPixelGameEngine.h"
#include "../collision/Collider.h"
#include <vector>

class Animation
{
private:
    // visual information
    olc::Decal* decal;
    olc::vf2d displacement{ 8, 3 };
    olc::vf2d sectionSize{ 32, 32 };
    olc::vf2d sectionPos{ 0, 0 };

    float elapsedFrame = 0.f;
    // number of horizontal states refers to the number of (different) animations within the sprite sheet
    int numberOfHorizontalStates = 0;
    // number of max vertical states is a suggestion of frames in the state due to the size of the sprite sheet
    int maxNumberOfVerticalStates = 0;
    // vertical frames refers to how many steps down do we go in multiples of section size before we flip to the top
    std::vector<int> verticalFrames;
    // time to remain in each frame in [x,y] format in seconds
    std::vector<std::vector<float>> frameThreshold;
private:

    void SetDefaultFrameThreshold(float time);
    void InitializeVerticalFrames();

public:
    float& currentState = sectionPos.x;
    float& currentFrame = sectionPos.y;
    bool flip = false;

    Animation(olc::Sprite& spriteSheet, olc::vi2d sectionSize, float timePerFrame = 0.1f);
    ~Animation();

    void ChangeVerticalFrameCount(int x, int newCount);
    void ChangeFrameThreshold(int x, int y, float newTime);
    void SetDisplacement(float x, float y);
    void SetSectionSize(float x, float y);
    void SetSectionPos(float x, float y);

    bool Animate(float fElapsedTime);
    void Draw(olc::PixelGameEngine &engine, Collider& current);
};