#include "Game.h"
#include "utility/settings/Settings.h"
#include "utility/AssetPath.h"

Game game;
Settings settings(GetAssetPath() + "settings.txt");

#include "network/server/Server.h"
#include "network/client/Client.h"
#include "utility/Signals.h"

#include <string>
#include <iostream>

#define OLC_PGEX_NETWORK
#include "olcPGEX_Network.h"

int startServer();
int startClient();
int testGame();
int Isoberry();

int main(int argc, char *argv[])
{
    if (argc > 1) {
        std::string firstArg = argv[1];

        if (firstArg.find("server") != std::string::npos) {
            return startServer();
        } else if (firstArg.find("client") != std::string::npos) {
            return startClient();
        } else if (firstArg.find("server1") != std::string::npos) {
            Server server;
            server.Run();
        }
    } else {
        if (game.Construct(settings.resolution.x, settings.resolution.y, settings.scale, settings.scale, settings.fullscreen, settings.vsync, true))
            game.Start();
    }
}