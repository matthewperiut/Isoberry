//
// Created by Matthew Periut on 5/24/21.
//

#pragma once

#include "../tool/v3.h"
#include "collision/Collider.h"
#include "../tool/layering/DrawOrderSystem.h"

class Object : public Collider
{
public:
    v3 position{ 0, 0, 0 };
    v3 velocity;
private:
    float fElapsedTime{};
    enum { XPos, XNeg, ZPos, ZNeg, YPos, YNeg };
    bool directions[6]{ false };

public:
    Object(const v3& size, const v3& position) : Collider(size, this->position)
    {
        this->position = position;
    }
    explicit Object(const v3& size) : Object(size, this->position)
    {

    }

private:
    bool NotCollidingWithAny(Collider& c, std::vector<Collider*>* cols);

    bool MoveXPos(std::vector<Collider*>* cols);
    bool MoveXNeg(std::vector<Collider*>* cols);
    bool MoveZPos(std::vector<Collider*>* cols);
    bool MoveZNeg(std::vector<Collider*>* cols);
    bool MoveYPos(std::vector<Collider*>* cols);
    bool MoveYNeg(std::vector<Collider*>* cols);
public:
    bool CollisionAbove();
    bool CollisionBelow();

    void setDecal(olc::Decal* decal);

    void Move(float fElapsedTime, DrawOrderSystem& dos);
};
