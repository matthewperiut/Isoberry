//
// Created by matthewperiut on 5/24/21.
//

#include "Physical.h"

bool Physical::NotCollidingWithAny(Collider &c, std::vector<Collider *> *cols) {
    for(auto & col : *cols)
    {
        if (col == (Collider*) this)
            continue;
        Collider& current = *col;
        if(current.isColliding(c))
            return false;
    }

    if(c.minY() < 0)
        return false;

    return true;
}

void Physical::Move(float fElapsedTime, DrawOrderSystem &dos)
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
        directions[YPos] = false;
        directions[YNeg] = false;
    }
}

// The reason for separating pos and neg even though seemingly
// unnecessary right now, it's for later optimization

bool Physical::MoveXPos(std::vector<Collider *> *cols)
{
    v3 pos = position;
    Collider temp = *this;
    temp.SetNewPosPointer(pos);
    pos.x += velocity.x * fElapsedTime;

    bool any = NotCollidingWithAny(temp, cols);

    if(any)
    {
        position.x = pos.x;
    }

    return !any;
}

bool Physical::MoveXNeg(std::vector<Collider *> *cols)
{
    v3 pos = position;
    Collider temp = *this;
    temp.SetNewPosPointer(pos);
    pos.x += velocity.x * fElapsedTime;

    bool any = NotCollidingWithAny(temp, cols);

    if(any)
    {
        (position).x = pos.x;
    }

    return !any;
}

bool Physical::MoveZPos(std::vector<Collider *> *cols)
{
    v3 pos = position;
    Collider temp = *this;
    temp.SetNewPosPointer(pos);
    pos.z += velocity.z * fElapsedTime;

    bool any = NotCollidingWithAny(temp, cols);

    if(any)
    {
        (position).z = pos.z;
    }

    return !any;
}

bool Physical::MoveZNeg(std::vector<Collider *> *cols)
{
    v3 pos = position;
    Collider temp = *this;
    temp.SetNewPosPointer(pos);
    pos.z += velocity.z * fElapsedTime;

    bool any = NotCollidingWithAny(temp, cols);

    if(any)
    {
        (position).z = pos.z;
    }

    return !any;
}

bool Physical::MoveYPos(std::vector<Collider *> *cols)
{
    v3 pos = position;
    Collider temp = *this;
    temp.SetNewPosPointer(pos);
    pos.y += velocity.y * fElapsedTime;

    bool any = NotCollidingWithAny(temp, cols);

    if(any)
    {
        (position).y = pos.y;
    }

    return !any;
}

bool Physical::MoveYNeg(std::vector<Collider *> *cols)
{
    v3 pos = position;
    Collider temp = *this;
    temp.SetNewPosPointer(pos);
    pos.y += velocity.y * fElapsedTime;

    bool any = NotCollidingWithAny(temp, cols);

    if(any)
    {
        (position).y = pos.y;
    }

    return !any;
}

bool Physical::CollisionAbove()
{
    return directions[YPos];
}

bool Physical::CollisionBelow()
{
    return directions[YNeg];
}

void Physical::setDecal(olc::Decal *decal)
{
    dec = decal;
}

void Physical::ApplyGravity() {
    if(hasGravity)
    {
        if(velocity.y > gravity*10)
        {
            velocity.y -= this->fElapsedTime*abs(gravity)*10;
        }
        else if (velocity.y < gravity*10)
        {
            velocity.y = gravity*10;
        }
    }
}
