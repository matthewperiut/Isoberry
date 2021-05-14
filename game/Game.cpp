//
// Created by matthewperiut on 5/7/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION
#include "Game.h"
#include "../utility/AssetPath.h"
#include "tool/input/Options.h"

Level l;

Game::Game() {
    sAppName = "Isoberry";
}

v3 pos{ 0, 0, 0 };

bool Game::OnUserCreate()
{
    Clear(olc::Pixel(52, 92, 72));
    l.LoadFromFile(GetAssetPath() + "levels/basis.txt");
    l.game = this;

    //Collider c = Collider(v3(40,50,30),pos);
    //c.DebugDraw(*this);

    return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{

    res.handle(*this);
    VSyncToggle(*this, fElapsedTime, olc::Key::F2);
    FullScreenToggle(*this, fElapsedTime, olc::Key::F3);

    l.DrawAll();

    /* for player later
    float movement = fElapsedTime * 20;
    v3 velocity{ 0, 0, 0 };
    GetKey(olc::Key::W).bHeld ? velocity.z =  1 : 0;
    GetKey(olc::Key::A).bHeld ? velocity.x = -1 : 0;
    GetKey(olc::Key::S).bHeld ? velocity.z = -1 : 0;
    GetKey(olc::Key::D).bHeld ? velocity.x =  1 : 0;
    GetKey(olc::Key::SPACE).bHeld ? velocity.y =  1 : 0;
    GetKey(olc::Key::SHIFT).bHeld ? velocity.y =  -1 : 0;
    if(velocity.x && velocity.z)
    {
        velocity.x *= 0.7;
        velocity.z *= 0.7;
    }
    position[0] += velocity * movement;
*/
    return true;
}

bool Game::OnUserDestroy()
{
    return true;
}