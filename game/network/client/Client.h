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

private:
    void Run();

public:
    Client();
    void StartThread(ClientBundle &clientBundle);
    ~Client();
};
