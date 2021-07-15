//
// Created by matthewperiut on 5/24/21.
//

#include "Shadow.h"

std::unique_ptr<olc::Sprite> shadowSpr;
std::unique_ptr<olc::Decal> shadowDec;

Shadow::Shadow(Collider& parent, DrawOrderSystem &DOS) : Collider(parent.GetSizeRef(), position), parent(&parent), DOS(&DOS)
{
    size.y = 1;
    position.y = -1;
}

void Shadow::CreateImages()
{
    if(shadowSpr == nullptr)
    {
        shadowSpr = std::make_unique<olc::Sprite>(GetAssetPath() + "shadow.png");
        shadowDec = std::make_unique<olc::Decal> (shadowSpr.get());
    }
    else
    {
        std::cout << "Shadow's CreateImages() is being called unnecessarily" << std::endl;
    }
}

void Shadow::UpdatePosition()
{
    position = v3(parent->GetPositionRef().x, -1, parent->GetPositionRef().z);

    //testing shadows
    while(DOS->IsColliding(*this))
    {
        position.y += 1;
        if(position.y > parent->minY())
        {
            position.y = parent->minY()-1;
            break;
        }
    }
    position.y = floor(position.y);
}

void Shadow::ApplyImage()
{
    if(applied)
        return;
    applied = true;
    dec = shadowDec.get();
    DOS->InsertObject(*this);
}

Shadow::~Shadow()
{
    if(applied)
    {
        DOS->RemoveObject(*this);
    }
}