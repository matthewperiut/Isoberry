//
// Created by matthewperiut on 9/5/21.
//

#pragma once

#include "collision/Physical.h"
#include "../tool/Img.h"

class Object : public Physical
{
public:
    Img* img = nullptr;
    Img* wireframe = nullptr;

public:
    Object(const v3 &size, const v3 &position);
    void AbsorbSpritePtr(olc::Sprite* sprite);
    void AbsorbImgPtr(Img* img);
    void AbsorbWireframe(olc::Sprite *sprite);
    std::string& GetFilePath();
    bool UpdateDec();
    ~Object();
};