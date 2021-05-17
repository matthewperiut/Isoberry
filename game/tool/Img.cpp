//
// Created by matthewperiut on 5/6/21.
//

#include "Img.h"
void Img::SetFilePath(std::string path)
{
    filePath = path;
    spr = std::make_unique<olc::Sprite>(filePath);
    dec = std::make_unique<olc::Decal>(spr.get());
}
void Img::SetImgSize(olc::vi2d size)
{
    spr = std::make_unique<olc::Sprite>(size.x, size.y);
    dec = std::make_unique<olc::Decal>(spr.get());
}

Img::Img()
{
    SetImgSize({ 10, 10 });
}
Img::Img(olc::vi2d size)
{
    SetImgSize(size);
}
Img::Img(std::string path)
{
    SetFilePath(path);
}
Img::Img(std::string path, olc::vi2d pos)
{
    SetFilePath(path);
    position = pos;
}

Img::Img(const Img &img)
{
    olc::Sprite& me = *this->spr.get();
    olc::Sprite& it = *img.spr.get();
    olc::vi2d size = olc::vi2d(it.width, it.height);
    SetImgSize(size);
    for(int i = 0; i < size.x; i++)
    {
        for(int j = 0; j < size.y; j++)
        {
            me.SetPixel(olc::vi2d(i,j), it.GetPixel(i,j));
        }
    }
    this->dec.get()->Update();
}

olc::Sprite* Img::GetSprPtr()
{
    return spr.get();
}
olc::Decal* Img::GetDecPtr()
{
    return dec.get();
}
std::string Img::GetFilePath()
{
    return filePath;
}