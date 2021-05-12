//
// Created by matthewperiut on 5/7/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION
#include "game.h"
#include "../utility/assetPath.h"

Game::Game() {
    sAppName = "Isoberry";
}

bool Game::OnUserCreate()
{
    Clear(olc::Pixel(52, 92, 72));
    other.DebugDraw(*this);

    test = new Img(GetAssetPath()+"test.png");
    trying = collider.CreateSpriteDebugDraw();
    trdec = new olc::Decal(trying);

    return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
    DrawDecal(olc::vf2d(0,0), test->GetDecPtr());
    DrawDecal(collider.GetTopLeft(olc::vf2d(0,0)),trdec);

    float movement = fElapsedTime * 20;
    v3 velocity{ 0, 0, 0 };
    GetKey(olc::Key::W).bHeld ? velocity.x = -1 : 0;
    GetKey(olc::Key::A).bHeld ? velocity.z = -1 : 0;
    GetKey(olc::Key::S).bHeld ? velocity.x =  1 : 0;
    GetKey(olc::Key::D).bHeld ? velocity.z =  1 : 0;
    if(velocity.x && velocity.z)
    {
        velocity.x *= 0.7;
        velocity.z *= 0.7;
    }
    position += velocity * movement;

    return true;
}

bool Game::OnUserDestroy() {
    delete trying;
    delete trdec;
    delete test;
    return true;
}