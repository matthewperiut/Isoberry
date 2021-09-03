//
// Created by matthewperiut on 5/24/21.
//

#pragma once

#include "collision/Collider.h"
#include "../tool/layering/DrawOrderSystem.h"
#include "../../utility/AssetPath.h"

/* Shadows
 * The plan is to divide up what is below an object
 * in levels and then make rectangular images to display
 * on each separate y level
 * They will be simple rectangles
 * There will be a derivative for entities which use a pixel perfect
 * circle below the player, which has a performant mode of using
 * a isometric circle image which only uses 1 y level
 */

class Shadow : public Collider
{
private:
    bool applied = false;
    DrawOrderSystem* DOS;
    v3 position;
    Collider* parent;

public:
    static void CreateImages();
    void ApplyImage();

    Shadow(Collider& parent, DrawOrderSystem &DOS);

    void UpdatePosition();

    ~Shadow();
};