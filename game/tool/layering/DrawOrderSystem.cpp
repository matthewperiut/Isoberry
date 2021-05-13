//
// Created by matthewperiut on 5/12/21.
//

#include "DrawOrderSystem.h"

void DrawOrderSystem::InsertObject(std::vector<Collider*> &vc, Collider *c)
{
    for(int i = 0; i < vc.size(); i++)
    {
        if(c->isAbove(*(vc[i])))
        {
            vc.insert(vc.begin()+i, c);
            break;
        }
    }
    //vc[0].
}


void DrawOrderSystem::InsertStaticObject(Collider *c)
{
    staticObjects.push_back(c);
}
void DrawOrderSystem::InsertDynamicObject(Collider *c)
{
    dynamicObjects.push_back(c);
}

void DrawOrderSystem::SortStaticObjects()
{

}



void DrawOrderSystem::UpdateDynamicObjects()
{

}

