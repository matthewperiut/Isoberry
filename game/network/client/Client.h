//
// Created by matthewperiut on 9/29/21.
//

#pragma once

#include <iostream>
#include <enet/enet.h>

class Client
{
public:
    bool running = true;

    ENetHost* client;
    ENetAddress address;
    ENetEvent event;
    ENetPeer* peer;

    Client();
    void Run();
    ~Client();
};
