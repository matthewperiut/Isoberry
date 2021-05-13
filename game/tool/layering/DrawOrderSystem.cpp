//
// Created by matthewperiut on 5/12/21.
//

#include "DrawOrderSystem.h"
#include <algorithm>

void DrawOrderSystem::InsertObject(Collider& c)
{
    objects.push_back(&c);
}

void DrawOrderSystem::SortObjects()
{
    auto sortRuleLambda = [] (Collider* &a, Collider* &b) -> bool
    {
        return !a->isAbove(*b);
    };

    std::sort(objects.begin(), objects.end(), sortRuleLambda);
}
