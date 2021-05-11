#include "game/game.h"
#include "utility/settings/settings.h"

Game game;
Settings settings("settings.txt");

int main() {
    if (game.Construct(settings.resolution.x, settings.resolution.y, settings.scale, settings.scale, settings.fullscreen, settings.vsync, true))
        game.Start();
    return 0;
}
