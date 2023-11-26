//
// Created by matthewperiut on 5/7/21.
//

#pragma once

#include <enet/enet.h>
#include "../tool/v3.h"
#include "collision/Physical.h"
#include "../utility/AssetPath.h"
#include "Shadow.h"
#include "../header/GlobalVariable.h"

class Player : public Physical
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
    // Network variables
    int id = -1;
    ENetPeer* peer;
    uint32_t host;
    uint16_t port;
    bool constructed = false;
    bool eraseMe = false;
public:
    void Construct()
    {
        constructed = true;
        isPlayer = true;
        isEntity = true;

        spriteSheets.emplace_back(new olc::Sprite(GetAssetPath() + "players/generic/generic-sprite.png"));
        decalSpriteSheets.emplace_back(new olc::Decal(spriteSheets[0]));

        DOS->InsertObject(*this);

        shadow.ApplyImage();
    }
    Player(const v3 &size, DrawOrderSystem& DOS) : Physical(size), shadow(*this, DOS), DOS(&DOS)
    {

    }
    Player(const v3& size, const v3& position, DrawOrderSystem& DOS) : Physical(size, position), shadow(*this, DOS), DOS(&DOS)
    {

    }
    void KeyboardInput(olc::PixelGameEngine& g);
    void Animate(float fElapsedTime);
    void Move(float fElapsedTime);

    Player operator= (Player player );
    ~Player()
    {
        for(int i = 0; i < spriteSheets.size(); i++)
        {
            garbage.sprites.push_back(spriteSheets[i]);
            garbage.decals.push_back(decalSpriteSheets[i]);
        }
        DOS->RemoveObject(*this);
    }
};
