//
// Created by matthewperiut on 5/12/21.
//

#pragma once

// Goal is to use no copy commands to minimize performance loss
// Ordering should be consistent, no variance from run to run.

// https://shaunlebron.github.io/IsometricBlocks/

#include "../../objects/collision/Collider.h"
#include <vector>

class DrawOrderSystem
{
private:
    std::vector<Collider*> objects;
    olc::PixelGameEngine* engine = nullptr;
public:

    DrawOrderSystem()
    = default;
    explicit DrawOrderSystem(olc::PixelGameEngine& g) : engine( &g )
    {}

    void InsertObject(Collider &c);
    void SortObjects();
    void RemoveObject(Collider &c);

    std::vector<Collider*>* GetObjects() { return &objects; }

    void DrawAll();

    bool IsColliding(Collider &participant);
};