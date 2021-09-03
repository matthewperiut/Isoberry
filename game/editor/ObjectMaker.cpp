//
// Created by matthewperiut on 9/3/2021.
//

#include "ObjectMaker.h"
#include "../../header/GlobalVariable.h"
#include "../tool/draw_sprites/DrawLineToSprite.h"

ObjectMaker::ObjectMaker() = default;

void ObjectMaker::SetGameEngine(olc::PixelGameEngine& engine)
{
    this->engine = &engine;
}
void ObjectMaker::SetDrawOrderSystem(DrawOrderSystem& DOS)
{
    if(this->DOS != nullptr)
    {
        this->DOS->RemoveObject(object);
    }

    this->DOS = &DOS;
    UpdateObjectSize();
    DOS.InsertObject(object);
}
void ObjectMaker::UpdateObjectSize()
{
    if(sprite != nullptr)
    {
        delete sprite;
        delete decal;
    }

    sprite = object.CreateSpriteDebugDraw();
    decal = new olc::Decal(sprite);
    object.dec = decal;
}
void ObjectMaker::ObjectMakerStudio(float fElapsedTime)
{
    if(engine->GetKey(olc::Key::L).bPressed)
    {
        active = !active;
        decal->Update();
    }
    if(!active)
        return;

    // 12 chars * 8 pixels = 96, plus 8 more for one space = 104
    engine->DrawStringDecal(olc::vf2d(engine->ScreenWidth()-(8*textMode.size())-104,0), "Object Maker");

    SelectMode(fElapsedTime);
    switch(mode)
    {
        case modes::clear:
            break;
        case modes::move:
            Move();
            break;
        case modes::resize:
            Resize();
            break;
    }
    object.Move(fElapsedTime, *DOS);
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
    engine->DrawStringDecal(olc::vf2d(engine->ScreenWidth()-(8*textMode.size()),0), textMode);
}

void ObjectMaker::SelectAxis()
{
    olc::Pixel color = olc::Pixel((axis=='X')*255,(axis=='Y')*255,(axis=='Z')*255);

    // Middle Mouse or Key M to activate drag select
    if(engine->GetKey(olc::Key::M).bHeld || engine->GetMouse(2).bHeld)
    {
        DrawLineToSprite(initialMouse.x, initialMouse.y, finalMouse.x, finalMouse.y, olc::BLANK, *debugOverlay);
        if(engine->GetKey(olc::Key::M).bPressed || engine->GetMouse(2).bPressed)
            initialMouse = engine->GetMousePos();
        finalMouse = engine->GetMousePos();
        int deltaX = (finalMouse.x - initialMouse.x);
        int deltaY = (finalMouse.y - initialMouse.y);
        float radians = atan2(deltaY, deltaX);
        if(radians > 0)
        {
            if(radians > 2)
                axis = 'Z';
            else if(radians < 1.11)
                axis = 'X';
            else
                axis = 'Y';
        }
        else
        {
            if(radians < -2)
                axis = 'X';
            else if(radians > -1.11)
                axis = 'Z';
            else
                axis = 'Y';
        }

        DrawLineToSprite(initialMouse.x, initialMouse.y, finalMouse.x, finalMouse.y, color, *debugOverlay);
        engine->DrawStringDecal(olc::vf2d(engine->ScreenWidth()-8, 8), std::string(1, axis), color);
        debugOverlayDecal->Update();
    }
    if(engine->GetKey(olc::Key::M).bReleased || engine->GetMouse(2).bReleased)
    {
        DrawLineToSprite(initialMouse.x, initialMouse.y, finalMouse.x, finalMouse.y, olc::BLANK, *debugOverlay);
        debugOverlayDecal->Update();
    }


    // Alternative X Y Z by keyboard
    if(engine->GetKey(olc::Key::X).bPressed)
        axis = 'X';
    if(engine->GetKey(olc::Key::Y).bPressed)
        axis = 'Y';
    if(engine->GetKey(olc::Key::Z).bPressed)
        axis = 'Z';
}
void ObjectMaker::Move()
{
    SelectAxis();

    v3& velocity = object.velocity;
    velocity = v3(0,0,0);
    v3 axisBasedDirection = v3((axis == 'X'),(axis == 'Y'),(axis == 'Z'));
    const v3 speed = v3(50,50,50);

    if(engine->GetMouseWheel() > 0)
    {
        object.velocity = axisBasedDirection * speed;
    }
    if(engine->GetMouseWheel() < 0)
    {
        object.velocity = -axisBasedDirection * speed;
    }

}
void ObjectMaker::Resize()
{
    SelectAxis();

    v3 axisBasedDirection = v3((axis == 'X'),(axis == 'Y'),(axis == 'Z'));
    v3& size = object.GetSizeRef();
    v3 oldSize = size;
    if(engine->GetMouseWheel() > 0)
    {
        size += axisBasedDirection;
    }
    else if(engine->GetMouseWheel() < 0)
    {
        size -= axisBasedDirection;
    }
    else
    {
        return;
    }
    if (DOS->IsColliding(object))
    {
        size = oldSize;
        return;
    }
    if (size.x < 1)
        size.x = 1;
    if (size.y < 1)
        size.y = 1;
    if (size.z < 1)
        size.z = 1;
    UpdateObjectSize();
}

Object ObjectMaker::GetObject()
{
    return object;
}

ObjectMaker::~ObjectMaker()
{
    if(sprite != nullptr)
    {
        delete sprite;
        delete decal;
    }
}