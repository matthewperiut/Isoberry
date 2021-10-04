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
    std::vector<Player>* players;
    std::vector<Level> levels;

    Server();
    void Run();
    ~Server();

    void AddPlayer(ENetEvent &ev);

    void RemovePlayer(ENetEvent &ev);

    int GetPlayerIndex(ENetPeer *peer);

    void SendByte(ENetEvent &ev, uint8_t data, uint8_t channel, bool toAll = false);

    void HandlePlayerPosition(ENetEvent &ev);

    void SendPlayerPosition(int index);
};