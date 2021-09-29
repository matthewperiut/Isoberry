#include "game/Game.h"
#include "utility/settings/Settings.h"
#include "utility/AssetPath.h"

// TODO: Multiplayer will inherit the ENET library
// http://enet.bespin.org/

Game game;
Settings settings(GetAssetPath() + "settings.txt");

#include "game/network/server/Server.h"
#include "game/network/client/Client.h"
#include "utility/Signals.h"

int main(int argc, char **argv)
{
    signal(SIGABRT, abort);

    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error has occurred while initializing ENet!\n");
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    for(int i = 1; i < argc; i++)
    {
        if(std::string(argv[i]) == "server")
        {
            Server server;
            server.Run();
            return 0;
        }
        std::cout << "Unrecognized argument: " << argv[i] << std::endl;
    }

    if (game.Construct(settings.resolution.x, settings.resolution.y, settings.scale, settings.scale, settings.fullscreen, settings.vsync, true))
        game.Start();
    return 0;
}
