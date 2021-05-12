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
    std::vector<Collider*> colliders;
    std::vector<olc::Decal*> decals;

    // Overlap calculation
};