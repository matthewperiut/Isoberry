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
    l.LoadFromFile(GetAssetPath() + "levels/basis.txt");
    l.game = this;

    shadow = new Collider(v3(10,1,10), shadowPosition);
    shadowImg = new Img(GetAssetPath() + "shadow.png");
    shadow->dec = shadowImg->GetDecPtr();
    l.DOS.InsertObject(*shadow);

    collider = new Collider(v3(10,10,10),position);
    img = new Img(GetAssetPath() + "10x10test_box.png");
    collider->dec = img->GetDecPtr();
    l.DOS.InsertObject(*collider);

    return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{

    res.handle(*this);
    VSyncToggle(*this, fElapsedTime, olc::Key::F2);
    FullScreenToggle(*this, fElapsedTime, olc::Key::F3);

    shadowPosition = position - v3(0,1,0);

/*
    std::vector<Collider*>* colliders = l.DOS.GetObjects();
    for(int i = shadowPosition.y-1; i > -2; i--)
    {
        bool stop = false;
        shadowPosition.y = i;
        for(int j = 0; j < colliders->size(); j++)
        {
            std::cout << j << std::endl;
            Collider* temp = (colliders->at(j));
            if(shadow->isColliding(*temp))
            {
                std::cout << "WEEWOO" << j << std::endl;
                stop = true;
            }
        }
        if(stop) break;
    }
    //shadowPosition.y+=1;
*/

    shadowPosition = v3(position.x, -1, position.z);

    l.DrawAll();

    //for player later
    v3 old = position;
    float movement = fElapsedTime * 20;
    v3 velocity{ 0, 0, 0 };
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
    position += velocity * movement;

    std::vector<Collider*>* colliders = l.DOS.GetObjects();
    for(int j = 0; j < colliders->size(); j++)
    {
        Collider* temp = (colliders->at(j));
        if(collider->isColliding(*temp))
        {
            if(collider->maxH() != temp->maxH())
            {
                position = old;
            }

        }
    }

    return true;
}

bool Game::OnUserDestroy()
{
    delete shadowImg;
    delete shadow;
    delete img;
    delete collider;
    return true;
}