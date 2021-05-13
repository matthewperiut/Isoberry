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
    int sizeX = 10;
    int sizeY = 10;
    position.reserve(sizeX * sizeY);
    colliders.reserve(sizeX * sizeY);

    for(int i = 0; i < sizeX; i++)
    {
        for(int j = 0; j < sizeY; j++)
        {
            position[i*sizeX+j] = v3(i*11-50,0,j*11-50);
            colliders[i*sizeX+j] = Collider(v3(10,10,10),position[i*sizeX+j]);
            dos.InsertObject(colliders[i*sizeX+j]);
        }

    }
    Collider temp = Collider(v3(10,10,10),position[0]);
    std::cout << GetAssetPath()+"10x10test_box.png" << std::endl;
    boxSpr = new olc::Sprite(GetAssetPath()+"10x10test_box.png");
    boxDec = new olc::Decal(boxSpr);

    return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{

    res.handle(*this);
    VSyncToggle(*this, fElapsedTime, olc::Key::F2);
    FullScreenToggle(*this, fElapsedTime, olc::Key::F3);

    // Sorting System DOS
    dos.SortObjects();
    std::vector<Collider*>* colliders = dos.GetObjects();
    for(int i = 0; i < colliders->size(); i++)
    {
        int color = (255/colliders->size())*i;
        Collider &current = *((*colliders)[i]);
        DrawDecal(current.GetTopLeft(olc::vf2d(0,0)), boxDec, olc::vf2d(1,1), olc::Pixel(color,color,color));
        //current.DebugDraw(*this);
    }

    /*
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
    */

    return true;
}

bool Game::OnUserDestroy()
{
    delete boxSpr;
    delete boxDec;
    return true;
}