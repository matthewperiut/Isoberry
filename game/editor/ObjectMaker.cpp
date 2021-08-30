#include "ObjectMaker.h"

void ObjectMaker::SetGameEngine(olc::PixelGameEngine& engine)
{
    this->engine = &engine;
}
void ObjectMaker::SetDrawOrderSystem(DrawOrderSystem& DOS)
{
    this->DOS = &DOS;
    DOS.InsertObject(object);
    UpdateObjectSize();
}
void ObjectMaker::UpdateObjectSize()
{
    if(sprite != nullptr)
    {
        delete sprite;
        delete decal;
    }

    olc::vi2d size = object.Get2dSize();

    sprite = object.CreateSpriteDebugDraw();
    decal = new olc::Decal(sprite);
}
void ObjectMaker::ObjectMakerStudio(float fElapsedTime)
{
    if(engine->GetKey(olc::Key::COMMA).bPressed)
        active = !active;
    if(!active)
        return;
    SelectMode(fElapsedTime);

}
void ObjectMaker::SelectMode(float fElapsedTime)
{
    countedTime += fElapsedTime;
    if(engine->GetKey(olc::Key::C).bPressed)
    {
        mode = modes::clear;
        textMode = "Clear";
        countedTime = 0;
    }
    if(engine->GetKey(olc::Key::G).bPressed)
    {
        mode = modes::move;
        textMode = "Move";
        countedTime = 0;
    }
    if(engine->GetKey(olc::Key::R).bPressed)
    {
        mode = modes::resize;
        textMode = "Resize";
        countedTime = 0;
    }
    if(countedTime < 5)
    {
        engine->DrawStringDecal(olc::vf2d(engine->ScreenWidth()-(8*textMode.size()),0), textMode);
    }
}
ObjectMaker::~ObjectMaker()
{
    if(sprite != nullptr)
    {
        delete sprite;
        delete decal;
    }
}