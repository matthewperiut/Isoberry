//
// Created by matthewperiut on 5/7/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION
#include "Game.h"
#include "../utility/AssetPath.h"
#include "tool/input/Options.h"

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

    Clear(olc::Pixel(52, 92, 72));

    res.handle(*this);
    VSyncToggle(*this, fElapsedTime, olc::Key::F2);
    FullScreenToggle(*this, fElapsedTime, olc::Key::F3);

    //DrawDecal(olc::vf2d(0,0), test->GetDecPtr());
    if(collider.isAbove(other))
    {
        DrawDecal(other.GetTopLeft(olc::vf2d(0,0)),trdec,olc::vf2d(1,1), olc::RED);
        DrawDecal(collider.GetTopLeft(olc::vf2d(0,0)),trdec);
    }
    else
    {
        DrawDecal(collider.GetTopLeft(olc::vf2d(0,0)),trdec);
        DrawDecal(other.GetTopLeft(olc::vf2d(0,0)),trdec,olc::vf2d(1,1), olc::RED);
    }

    //other.DebugDraw(*this);
    //TOP Draw(other.CornerOnScreen(1,0,0), olc::RED);
    //BOTTOM Draw(other.CornerOnScreen(0,1,1), olc::RED);

    if(other.Overlaps(collider))
        Draw(0,0,olc::RED);
    else
        Draw(0,0,olc::BLACK);

    DrawLine(other.maxH(), 0, other.maxH(), 200, olc::RED);
    DrawLine(other.minH(), 0, other.minH(), 200, olc::RED);
    DrawLine(collider.maxH(), 0, collider.maxH(), 200, olc::RED);
    DrawLine(collider.minH(), 0, collider.minH(), 200, olc::RED);

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
    position += velocity * movement;

    return true;
}

bool Game::OnUserDestroy() {
    delete trying;
    delete trdec;
    delete test;
    return true;
}