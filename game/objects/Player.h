//
// Created by matthewperiut on 5/7/21.
//

#pragma once

#include "../tool/v3.h"
#include "Object.h"
#include "../../utility/AssetPath.h"
#include "Shadow.h"

class Player : public Object
{
private:
    DrawOrderSystem* DOS;

    // animation
    std::vector<olc::Sprite*> spriteSheets;
    float& frame = sectionPos.y;
    float& state = sectionPos.x;
    float elapsedFrame = 0.f;
    float thresholdTime = 0.1f;
    int rotationState = 0;
    // in X refers to in the sprite sheet which set of animations
    const int avaliableFramesInX[5] = {8,8,8,8,8};

    Shadow shadow;

    // movement
    bool jump = false;
    bool hasLetGoJump = true;

public:
    void Construct()
    {
        isPlayer = true;
        isEntity = true;

        spriteSheets.emplace_back(new olc::Sprite(GetAssetPath() + "players/generic/generic-sprite.png"));
        decalSpriteSheets.emplace_back(new olc::Decal(spriteSheets[0]));

        DOS->InsertObject(*this);

        shadow.ApplyImage();
    }
    Player(const v3 &size, DrawOrderSystem& DOS) : Object(size), shadow(*this, DOS), DOS(&DOS)
    {

    }
    Player(const v3& size, const v3& position, DrawOrderSystem& DOS) : Object(size, position), shadow(*this, DOS), DOS(&DOS)
    {

    }
    void KeyboardInput(olc::PixelGameEngine& g);
    void Animate(float fElapsedTime);
    void Move(float fElapsedTime);
    ~Player()
    {
        for(int i = 0; i < spriteSheets.size(); i++)
        {
            delete spriteSheets[i];
            delete decalSpriteSheets[i];
        }
        DOS->RemoveObject(*this);
    }
};
