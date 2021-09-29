//
// Created by matthewperiut on 9/27/21.
//

#pragma once

#include <iostream>
#include <filesystem>

#include <enet/enet.h>
#include "../../objects/Player.h"
#include "../../level/Level.h"
#include "ServerGUI.h"

class Server
{
public:
    bool running = true;

    ServerGUI gui = ServerGUI(running);
    std::thread serverThread;

    ENetAddress address;
    ENetHost *server;
    ENetEvent event;

    std::vector<ENetHost*> clients;
    std::vector<Player> players;
    std::vector<Level> levels;

    Server();
    void Run();
    ~Server();
};