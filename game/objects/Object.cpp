//
// Created by matthewperiut on 9/5/21.
//

#include "Object.h"

Object::Object(const v3 &size, const v3 &position) : Physical(size, position)
{

}

void Object::AbsorbSpritePtr(olc::Sprite* sprite)
{
    this->img = new Img(sprite);
}

void Object::AbsorbImgPtr(Img *img)
{
    this->img = img;
}

void Object::AbsorbWireframe(olc::Sprite* sprite)
{
    this->wireframe = new Img(sprite);
}

bool Object::UpdateDec()
{
    if(img == nullptr)
    {
        if(wireframe == nullptr)
        {
            return false;
        }
        this->dec = wireframe->GetDecPtr();
    }
    else
    {
        this->dec = img->GetDecPtr();
    }

    return true;
}

std::string& Object::GetFilePath()
{
    return img->GetFilePath();
}

Object::~Object()
{
    if(img != nullptr)
    {
        delete img;
    }
    if(wireframe != nullptr)
    {
        delete wireframe;
    }
}