//
// Created by matthewperiut on 5/14/2021.
//

#include "Level.h"
#include "../utility/AssetPath.h"

void Level::LoadFromFile(std::string path, bool withImages)
{
    std::ifstream file(path);
    std::string line;
    while(std::getline(file, line))
    {
        std::istringstream stream(line);
        std::string mode;
        stream >> mode;

        if (mode == "BOX")
        {
            {
                v3 p, s;
                if(stream >> p.x >> p.y >> p.z >> s.x >> s.y >> s.z)
                {
                    objects.push_back(new Object(s, p));
                }
                else
                {
                    continue;
                }
            }

            if(!withImages)
                continue;

            Object& current = *objects[objects.size()-1];

            current.AbsorbWireframe(current.CreateSpriteDebugDraw(olc::Pixel(rand()%255,rand()%255,rand()%255)));

            std::string path;
            if (stream >> path)
            {
                current.AbsorbImgPtr(new Img(GetAssetPath() + path));
            }

            current.UpdateDec();
            DOS.InsertObject(current);
        }
        if (mode == "NAME")
        {
            stream >> name;
        }
    }
}

void Level::DrawAll()
{
    DOS.DrawAll();
}

Level::~Level()
{
    for(int i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
}

Level::Level()
{

}

void Level::Loop(float fElapsedTime)
{
    for(int i = 0; i < players.size(); i++)
    {
        if(!players[i].constructed)
            players[i].Construct();
        if(players[i].eraseMe)
            players.erase(players.begin() + i);
        players[i].Move(fElapsedTime);
    }
}
