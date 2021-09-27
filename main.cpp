#include "game/Game.h"
#include "utility/settings/Settings.h"
#include "utility/AssetPath.h"

// TODO: Multiplayer will inherit the ENET library
// http://enet.bespin.org/

Game game;
Settings settings(GetAssetPath() + "settings.txt");

int main()
{
    if (game.Construct(settings.resolution.x, settings.resolution.y, settings.scale, settings.scale, settings.fullscreen, settings.vsync, true))
        game.Start();
    return 0;
}
