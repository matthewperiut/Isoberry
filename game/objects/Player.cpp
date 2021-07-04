//
// Created by matthewperiut on 5/7/21.
//

#include "Player.h"

void Player::KeyboardInput(olc::PixelGameEngine& g)
{
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
    if(CollisionBelow())
    {
        // using bHeld bc CollisionBelow isn't reliable (yet)
        if(g.GetKey(olc::Key::SPACE).bHeld && hasLetGoJump)
        {
            velocity.y = 85;
            hasLetGoJump = false;
        }

        jump = true;
    }
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
}

void Player::Move(float fElapsedTime, DrawOrderSystem &dos)
{
    Object::Move(fElapsedTime, dos);

    if(CollisionBelow())
        velocity.y = 0;
}