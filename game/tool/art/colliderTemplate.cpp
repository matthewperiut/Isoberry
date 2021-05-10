//
// Created by matthewperiut on 5/10/21.
//

#include "colliderTemplate.h"
#include "../SpriteSaving/saving.h"
void MakeTemplateCollider(v3 size, std::string path)
{
    Collider c(v3(0,0,0), size);
    SaveSprite(c.CreateSpriteDebugDraw(), path);
}