#include "game/Game.h"
#include "utility/settings/Settings.h"
#include "utility/AssetPath.h"
#include <enet/enet.h>
#include <boxer/boxer.h>
//#include <openssl/ssl.h>

// TODO: Multiplayer will inherit the ENET library
// http://enet.bespin.org/

Game game;
Settings settings(GetAssetPath() + "settings.txt");

int main()
{
    if (enet_initialize())
    {
        boxer::show("ENet has not initialized correctly.", "ENet Failure", boxer::Style::Error);
        return 0;
    }

    if (game.Construct(settings.resolution.x, settings.resolution.y, settings.scale, settings.scale, settings.fullscreen, settings.vsync, true))
        game.Start();
    return 0;
}
