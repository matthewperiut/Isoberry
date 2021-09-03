//
// Created by matthewperiut on 5/14/2021.
//

#include "Level.h"
#include "../../utility/AssetPath.h"

void Level::LoadFromFile(std::string path)
{
    std::ifstream file(path);
    std::string out;
    while(file >> out)
    {
        if(out == "RESERVE")
        {
            file >> numberReserved;
            for(int i = 0; i < numberReserved; i++)
            {
                images.emplace_back();
                positions.emplace_back();
                colliders.emplace_back(v3(10,10,10), tempPos);
            }
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

            int imgIndex = numberImported;
            bool found = false;
            std::string imgPath;
            file >> imgPath;
            for(int i = 0; i < numberImported; i++)
            {
                if(*(imgpaths[i]) == imgPath)
                {
                    imgIndex = i;
                    found = true;
                }
            }
            if(!found)
            {
                images[numberImported] = new Img(GetAssetPath() + imgPath);
                imgpaths.push_back(&(images[numberImported]->filePath));
            }

            c.dec = images[imgIndex]->GetDecPtr();
            DOS.InsertObject(c);

            numberImported++;
        }
    }
}

void Level::DrawAll()
{
    DOS.DrawAll();
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
