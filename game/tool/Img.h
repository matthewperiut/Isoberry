#pragma once
#include "../../header/olcPixelGameEngine.h"
#include <memory>
#include <string>

class Img
{
public:
    std::string filePath;

private:
    std::unique_ptr<olc::Sprite> spr;
    std::unique_ptr<olc::Decal> dec;

public:
    olc::vi2d position{ 0, 0 };

public:
    void SetFilePath(std::string path);
    void SetImgSize(olc::vi2d size);

    Img();
    Img(olc::vi2d size);
    Img(std::string path);
    Img(std::string path, olc::vi2d pos);
    Img(olc::Sprite* sprPtr);
    Img(const Img &img);

    olc::Sprite* GetSprPtr();
    olc::Decal* GetDecPtr();
    std::string& GetFilePath();
};