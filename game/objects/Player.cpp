//
// Created by matthewperiut on 5/7/21.
//

#include "Player.h"

void Player::KeyboardInput(olc::PixelGameEngine& g)
{
    if(g.GetKey(olc::Key::SPACE).bReleased)
    {
        hasLetGoJump = true;
        if(jump)
        {
            if (velocity.y > 0)
                velocity.y = velocity.y*0.5;
            jump = false;
        }
    }

    if(!CollisionBelow())
        return;
    else
    {
        // using bHeld bc CollisionBelow isn't reliable (yet)
        if(g.GetKey(olc::Key::SPACE).bHeld && hasLetGoJump)
        {
            velocity.y = 90;
            hasLetGoJump = false;
        }

        jump = true;
    }

    velocity.x = 0;
    velocity.z = 0;

    g.GetKey(olc::Key::W).bHeld ? velocity.z = 30 : 0;
    g.GetKey(olc::Key::A).bHeld ? velocity.x = -30 : 0;
    g.GetKey(olc::Key::S).bHeld ? velocity.z = -30 : 0;
    g.GetKey(olc::Key::D).bHeld ? velocity.x = 30 : 0;

    if (abs(velocity.x + velocity.z) == 60) {
        velocity.x *= 0.7;
        velocity.z *= 0.7;
    }
}

void Player::Move(float fElapsedTime, DrawOrderSystem &dos)
{
    Object::Move(fElapsedTime, dos);

    if(CollisionBelow())
        velocity.y = 0;

    Animate(fElapsedTime);
}

void Player::Animate(float fElapsedTime)
{


    if(!jump || !hasLetGoJump)
        return;

    if(abs(velocity.x) + abs(velocity.z) == 0)
    {
        frame = 1;
        return;
    }

    elapsedFrame += fElapsedTime;
    if(elapsedFrame < thresholdTime)
        return;
    elapsedFrame = 0;
    frame++;

    if(frame == avaliableFramesInX[int(state)])
    {
        frame = 0;
    }

    if(velocity.z != 0 && velocity.x == 0)
    {
        if(velocity.z < 0)
            rotationState = 0;
        if(velocity.z > 0)
            rotationState = 7; // reverse
    }

    if(velocity.z == 0 && velocity.x != 0)
    {
        if(velocity.x < 0)
            rotationState = 2;
        if(velocity.x > 0)
            rotationState = 5; // reverse
    }

    if(velocity.z > 0)
    {
        if(velocity.x > 0)
        {
            rotationState = 6;
        }
        if(velocity.x < 0)
        {
            rotationState = 3; // reverse
        }
    }
    if(velocity.z < 0)
    {
        if(velocity.x > 0)
        {
            rotationState = 4;
        }
        if(velocity.x < 0)
        {
            rotationState = 1;
        }
    }

    if (rotationState < 5)
    {
        state = rotationState;
        displacement = { 8, 3 };
        flip = 0;
    }
    else
    {
        state = rotationState - 5;
        flip = 1;
        displacement = { 8, 3 };
    }
}
