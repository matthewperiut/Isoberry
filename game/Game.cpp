//
// Created by matthewperiut on 5/7/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION
#include "Game.h"
#include "../utility/AssetPath.h"
#include "tool/input/Options.h"
#include "objects/Object.h"

Object test(v3(10,10,10), v3(-20,1,-20));

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
    /*
       collider = new Collider(v3(10,10,10),position);
       img = new Img(GetAssetPath() + "10x10test_box.png");
       collider->dec = img->GetDecPtr();
       l.DOS.InsertObject(*collider);
   */
    img = new Img(GetAssetPath() + "10x10test_box.png");
    test.setDecal(img->GetDecPtr());
    l.DOS.InsertObject(test);
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
/*
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

    shadowPosition = v3(test.position.x, -1, test.position.z);

    //testing
    while(l.DOS.IsColliding(*shadow))
    {
        shadowPosition.y += 1;
    }
/*
    l.DrawAll();

    //for player later
    v3 old = position;
    float movement = fElapsedTime * 20;
    v3 velocity{ 0, 0, 0 };
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
            if(collider != temp)
            {
                position = old;
            }

        }
    }
*/
    v3& velocity = test.velocity;
    velocity = {0,0,0};
    GetKey(olc::Key::W).bHeld ? velocity.z =  1 : 0;
    GetKey(olc::Key::A).bHeld ? velocity.x = -1 : 0;
    GetKey(olc::Key::S).bHeld ? velocity.z = -1 : 0;
    GetKey(olc::Key::D).bHeld ? velocity.x =  1 : 0;
    GetKey(olc::Key::UP).bHeld ? velocity.y =  1 : 0;
    GetKey(olc::Key::DOWN).bHeld ? velocity.y =  -1 : 0;
    velocity *= 30;
    test.Move(fElapsedTime, l.DOS);
    l.DOS.DrawAll();
    return true;
}

void SafeDelete(void* anything)
{
    if (anything != nullptr)
        delete anything;
}

bool Game::OnUserDestroy()
{
    SafeDelete(shadowImg);
    SafeDelete(shadow);
    SafeDelete(img);
    SafeDelete(collider);
    return true;
}