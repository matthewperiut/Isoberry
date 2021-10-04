//
// Created by matthewperiut on 9/29/21.
//

#pragma once

#include <iostream>
#include <enet/enet.h>
#include "ClientBundle.h"

class Client
{
public:
    std::thread clientThread;
    ClientBundle* clientBundle;
    bool running = true;
    bool connected = false;

    ENetHost* client;
    ENetAddress address;
    ENetEvent event;
    ENetPeer* peer;

    std::vector<Player>* players;

private:
    void Run();

public:
    Client();
    void StartThread(ClientBundle &clientBundle);
    ~Client();

    void SendPlayerData();

    int GetPlayerIndex(int id);

    void HandleID(ENetEvent &ev);

    void HandlePositions(ENetEvent &ev);

    void SetLevel(Level &level);
};
