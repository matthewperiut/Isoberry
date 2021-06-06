//
// Created by Matthew Periut on 5/24/21.
//

#include "Object.h"

bool Object::CollidingWithAny(Collider &c, std::vector<Collider *> *cols) {
    for(auto & col : *cols)
    {
        Collider& current = *col;
        if(current.isColliding(c))
            return true;
    }
    return false;
}

void Object::Move(float fElapsedTime, DrawOrderSystem &dos)
{
    this->fElapsedTime = fElapsedTime;
    std::vector<Collider*>* cols;
    cols = dos.GetObjects();
    if(velocity.x < 0)
    {
        directions[XPos] = false;
        directions[XNeg] = MoveXNeg(cols);
    }
    else if(velocity.x > 0)
    {
        directions[XPos] = MoveXPos(cols);
        directions[XNeg] = false;
    }
    else
    {
        directions[XPos] = false;
        directions[XNeg] = false;
    }
    if(velocity.z < 0)
    {
        directions[ZPos] = false;
        directions[ZNeg] = MoveZNeg(cols);
    }
    else if (velocity.z > 0)
    {
        directions[ZPos] = MoveZPos(cols);
        directions[ZNeg] = false;
    }
    else
    {
        directions[ZPos] = false;
        directions[ZNeg] = false;
    }
    if(velocity.y < 0)
    {
        directions[YPos] = false;
        directions[YNeg] = MoveYNeg(cols);
    }
    else if(velocity.y > 0)
    {
        directions[YPos] = MoveYPos(cols);
        directions[YNeg] = false;
    }
    else
    {
        directions[YPos] = 0;
        directions[YNeg] = 0;
    }
}

// The reason for separating pos and neg even though seemingly
// unnecessary right now, it's for later optimization

bool Object::MoveXPos(std::vector<Collider *> *cols)
{
    v3 pos = *position;
    Collider temp = *this;
    temp.SetNewPosPointer(pos);
    pos.x += velocity.x * fElapsedTime;

    bool any = CollidingWithAny(temp, cols);

    if(any)
    {
        (*position).x = pos.x;
    }

    return any;
}

bool Object::MoveXNeg(std::vector<Collider *> *cols)
{
    v3 pos = *position;
    Collider temp = *this;
    temp.SetNewPosPointer(pos);
    pos.x += velocity.x * fElapsedTime;

    bool any = CollidingWithAny(temp, cols);

    if(any)
    {
        (*position).x = pos.x;
    }

    return any;
}

bool Object::MoveZPos(std::vector<Collider *> *cols)
{
    v3 pos = *position;
    Collider temp = *this;
    temp.SetNewPosPointer(pos);
    pos.z += velocity.z * fElapsedTime;

    bool any = CollidingWithAny(temp, cols);

    if(any)
    {
        (*position).z = pos.z;
    }

    return any;
}

bool Object::MoveZNeg(std::vector<Collider *> *cols)
{
    v3 pos = *position;
    Collider temp = *this;
    temp.SetNewPosPointer(pos);
    pos.z += velocity.z * fElapsedTime;

    bool any = CollidingWithAny(temp, cols);

    if(any)
    {
        (*position).z = pos.z;
    }

    return any;
}

bool Object::MoveYPos(std::vector<Collider *> *cols)
{
    v3 pos = *position;
    Collider temp = *this;
    temp.SetNewPosPointer(pos);
    pos.y += velocity.y * fElapsedTime;

    bool any = CollidingWithAny(temp, cols);

    if(any)
    {
        (*position).y = pos.y;
    }

    return any;
}

bool Object::MoveYNeg(std::vector<Collider *> *cols)
{
    v3 pos = *position;
    Collider temp = *this;
    temp.SetNewPosPointer(pos);
    pos.y += velocity.y * fElapsedTime;

    bool any = CollidingWithAny(temp, cols);

    if(any)
    {
        (*position).y = pos.y;
    }

    return any;
}

bool Object::CollisionAbove()
{
    return directions[YPos];
}

bool Object::CollisionBelow()
{
    return directions[XPos];
}

void Object::setDecal(olc::Decal *decal)
{
    dec = decal;
}
