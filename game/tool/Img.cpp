//
// Created by matthewperiut on 5/6/21.
//

#include "Img.h"
void Img::SetFilePath(string path)
{
    filePath = path;
    spr = std::make_unique<olc::Sprite>(filePath);
    dec = std::make_unique<olc::Decal>(spr.get());
}
void Img::SetImgSize(vi2d size)
{
    spr = std::make_unique<olc::Sprite>(size.x, size.y);
    dec = std::make_unique<olc::Decal>(spr.get());
}

Img::Img()
{
    SetImgSize({ 10, 10 });
}
Img::Img(vi2d size)
{
    SetImgSize(size);
}
Img::Img(string path)
{
    SetFilePath(path);
}
Img::Img(string path, vi2d pos)
{
    SetFilePath(path);
    position = pos;
}

Img::Img(const Img &img)
{
    Sprite& me = *this->spr.get();
    Sprite& it = *img.spr.get();
    vi2d size = vi2d(it.width, it.height);
    SetImgSize(size);
    for(int i = 0; i < size.x; i++)
    {
        for(int j = 0; j < size.y; j++)
        {
            me.SetPixel(vi2d(i,j), it.GetPixel(i,j));
        }
    }
    this->dec.get()->Update();
}

Sprite* Img::GetSprPtr()
{
    return spr.get();
}
Decal* Img::GetDecPtr()
{
    return dec.get();
}
string Img::GetFilePath()
{
    return filePath;
}