//
// Created by matthewperiut on 9/27/21.
//

#include "Server.h"

Server::Server()
{
    serverThread = std::thread(&Server::Run, this);

    if(gui.Construct(256,144,4,4,false,true))
        gui.Start();
}

void Server::Run()
{
    gui.InsertMessage("Starting Server...");

    address.host = ENET_HOST_ANY;
    address.port = 47623; // ISOBE as phone number

    server = enet_host_create(&address, 32, 1, 0, 0);

    if (server == nullptr)
    {
        gui.InsertMessage("[Stopping Server] Error Creating Server");
        return;
    }

    gui.InsertMessage("Port:" + std::to_string(address.port));

    while(running)
    {
        while(enet_host_service(server, &event, 1000) > 0)
        {
            switch(event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                    gui.InsertMessage("A new client connected from " +
                                      std::to_string(event.peer -> address.host) + ":" +
                                      std::to_string(event.peer -> address.port));
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    gui.InsertMessage("A packet of length " +
                                      std::to_string(event.packet -> dataLength) + " containing " +
                                      std::string(reinterpret_cast<char*>(event.packet -> data)) + " was received from " +
                                      std::to_string(event.peer -> address.host) + ":" +
                                      std::to_string(event.peer -> address.port) + " on channel " +
                                      std::to_string(event.channelID));
                    break;
                case ENET_EVENT_TYPE_NONE:
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    gui.InsertMessage(std::to_string(event.peer -> address.host) + ":" + std::to_string(event.peer -> address.port) + "Disconnected");
                    break;
            }
        }
    }
    gui.InsertMessage("Stopping Server...");
}

Server::~Server()
{
    enet_host_destroy(server);
}