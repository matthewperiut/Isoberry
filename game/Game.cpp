//
// Created by matthewperiut on 5/7/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION
#include "Game.h"
#include "../utility/AssetPath.h"
#include "tool/input/Options.h"
#include "objects/Object.h"

Game::Game() {
    sAppName = "Isoberry";
}

bool Game::OnUserCreate()
{

    Clear(olc::Pixel(52, 92, 72));
    l = Level(*this);
    l.LoadFromFile(GetAssetPath() + "levels/basis.txt");

    shadow = new Collider(v3(10,1,10), shadowPosition);
    shadowImg = new Img(GetAssetPath() + "shadow.png");
    shadow->dec = shadowImg->GetDecPtr();
    l.DOS.InsertObject(*shadow);

    img = new Img(GetAssetPath() + "10x10x10player.png");
    test.setDecal(img->GetDecPtr());
    l.DOS.InsertObject(test);
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{

    shadowPosition = v3(test.position.x, -1, test.position.z);

    //testing shadows
    while(l.DOS.IsColliding(*shadow))
    {
        shadowPosition.y += 1;
        if(shadowPosition.y > test.minY())
        {
            shadowPosition.y = test.minY()-1;
            break;
        }
    }
    shadowPosition.y = floor(shadowPosition.y);

    //testing player
    v3& velocity = test.velocity;
    velocity = {0,0,0};
    GetKey(olc::Key::W).bHeld ? velocity.z =  1 : 0;
    GetKey(olc::Key::A).bHeld ? velocity.x = -1 : 0;
    GetKey(olc::Key::S).bHeld ? velocity.z = -1 : 0;
    GetKey(olc::Key::D).bHeld ? velocity.x =  1 : 0;
    GetKey(olc::Key::UP).bHeld ? velocity.y =  1 : 0;
    GetKey(olc::Key::DOWN).bHeld ? velocity.y =  -1 : 0;
    if(velocity.x && velocity.z)
    {
        velocity.x *= 0.7;
        velocity.z *= 0.7;
    }
    velocity *= 30;
    test.Move(fElapsedTime, l.DOS);
    l.DOS.DrawAll();
    return true;
}

bool Game::OnUserDestroy()
{
    delete shadowImg;
    delete shadow;
    delete img;
    return true;
}