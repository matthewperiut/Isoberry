//
// Created by matthewperiut on 5/7/21.
//

#include "Player.h"

void Player::KeyboardInput(olc::PixelGameEngine& g) {
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

    g.GetKey(olc::Key::SPACE).bPressed ? velocity.y = 70 : 0;
    g.GetKey(olc::Key::SPACE).bReleased ? velocity.y = velocity.y*0.7 : velocity.y;
}