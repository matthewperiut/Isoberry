//
// Created by matthewperiut on 5/12/21.
//

#include "DrawOrderSystem.h"
#include <algorithm>

bool DrawOrderSystem::IsColliding(Collider& participant)
{
    std::vector<Collider*>* colliders = GetObjects();
    for(auto & col : *colliders)
    {
        if (col == &participant)
            continue;
        if(participant.isColliding(*col))
            return true;
    }
    return false;
}

void DrawOrderSystem::InsertObject(Collider& c)
{
    objects.push_back(&c);
}

void DrawOrderSystem::RemoveObject(Collider &c)
{
    for(int i = 0; i < objects.size(); i++)
    {
        if(objects[i] == &c)
        {
            objects.erase(objects.begin() + i);
            return;
        }
    }
}

void DrawOrderSystem::SortObjects()
{
    auto sortRuleLambda = [] (Collider* &a, Collider* &b) -> bool
    {
        return !a->isAbove(*b);
    };

    std::sort(objects.begin(), objects.end(), sortRuleLambda);
}

void DrawOrderSystem::DrawAll()
{
    SortObjects();
    std::vector<Collider*>* colliders = GetObjects();
    for(int i = 0; i < colliders->size(); i++)
    {
        Collider &current = *((*colliders)[i]);
        if(current.dec == nullptr)
        {
            for(int j = 0; j < current.decalSpriteSheets.size(); j++)
            {

                engine->DrawPartialDecal(current.GetTopLeft(-current.displacement)+(current.flip*olc::vf2d(current.sectionSize.x,0)),
                                         current.decalSpriteSheets[j],
                                         current.sectionPos*current.sectionSize, current.sectionSize,
                                         olc::vf2d(1 - (current.flip*2),1));
            }
            continue;
        }
        engine->DrawDecal(current.GetTopLeft(olc::vf2d(0,0)), current.dec);
    }
}