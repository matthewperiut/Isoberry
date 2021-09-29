//
// Created by matthewperiut on 9/27/21.
//

#pragma once

#include <iostream>
#include <filesystem>

#include <enet/enet.h>
#include "../../objects/Player.h"
#include "../../level/Level.h"

class Server
{
public:
    bool running = true;

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