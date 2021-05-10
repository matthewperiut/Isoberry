#include <iostream>

#include "game/game.h"
#include "utility/settings/settings.h"
#include "game/tool/art/colliderTemplate.h"
#include "game/tool/SpriteSaving/saving.h"

Game game;
Settings settings("settings.txt");

int main() {
    //olc::Sprite* gg = new olc::Sprite(10,10);
    if (game.Construct(settings.resolution.x, settings.resolution.y, settings.scale, settings.scale, settings.fullscreen, settings.vsync, true))
        game.Start();
    return 0;
}
