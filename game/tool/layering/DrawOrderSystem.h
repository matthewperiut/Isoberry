//
// Created by matthewperiut on 5/12/21.
//

#pragma once

// Goal is to use no copy commands to minimize performance loss
// Ordering should be consistent, no variance from run to run.

// https://shaunlebron.github.io/IsometricBlocks/

#include "../collision/Collider.h"
#include <vector>

class DrawOrderSystem
{
private:
    std::vector<Collider*> staticObjects;
    std::vector<Collider*> dynamicObjects;
    std::vector<Collider*> combinedObjects;

    static void InsertObject(std::vector<Collider*> &vc, Collider* c);
public:
    void InsertStaticObject(Collider* c);
    void InsertDynamicObject(Collider* c);
    void UpdateDynamicObjects();

    std::vector<Collider*>* GetObjects() { return &combinedObjects; }

    // Overlap calculation
    void SortStaticObjects();
};