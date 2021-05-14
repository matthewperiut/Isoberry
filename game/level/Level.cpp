//
// Created by Matthew on 5/14/2021.
//

#include "Level.h"
#include "../../utility/AssetPath.h"

void Level::LoadFromFile(std::string path)
{
    std::ifstream file(path);
    string out;
    while(file >> out)
    {
        if(out == "RESERVE")
        {
            file >> numberReserved;
            images.reserve(numberReserved);
            positions.reserve(numberReserved);
            colliders.reserve(numberReserved);
        }
        if(out == "BOX")
        {
            v3& p = positions[numberImported];
            p = v3(0,0,0);
            file >> p.x >> p.y >> p.z;

            //s = size
            v3 s = v3(0,0,0);
            file >> s.x >> s.y >> s.z;

            Collider& c = colliders[numberImported];
            c = Collider(s, p);

            std::string imgPath;
            file >> imgPath;
            images[numberImported] = new Img(GetAssetPath() + imgPath);

            c.dec = images[numberImported]->GetDecPtr();
            DOS.InsertObject(c);

            numberImported++;
        }
    }
}

void Level::DrawAll()
{
    DOS.SortObjects();
    std::vector<Collider*>* colliders = DOS.GetObjects();
    for(int i = 0; i < numberImported; i++)
    {
        Collider &current = *((*colliders)[i]);
        game->DrawDecal(current.GetTopLeft(olc::vf2d(0,0)), current.dec);
    }
}

Level::~Level()
{
    for(int i = 0; i < numberImported; i++)
    {
        delete images[i];
    }
}

Level::Level()
{

}
