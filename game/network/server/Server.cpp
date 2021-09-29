//
// Created by matthewperiut on 9/27/21.
//

#include "Server.h"

Server::Server()
{
    std::cout << "Server Starting..." << std::endl;

    address.host = ENET_HOST_ANY;
    address.port = 47623; // ISOBE as phone number

    server = enet_host_create(&address, 32, 1, 0, 0);

    if (server == nullptr)
    {
        std::cout << "Error occurred while creating the Server" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << address.host << ":" << address.port << std::endl;
}

void Server::Run()
{
    while(running)
    {
        while(enet_host_service(server, &event, 1000) > 0)
        {
            switch(event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                    printf ("A new client connected from %x:%u.\n",
                            event.peer -> address.host,
                            event.peer -> address.port);
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    printf ("A packet of length %zu containing %s was received from %x:%u on channel %u.\n",
                            event.packet -> dataLength,
                            event.packet -> data,
                            event.peer -> address.host,
                            event.peer -> address.port,
                            event.channelID);
                    break;
                case ENET_EVENT_TYPE_NONE:
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    printf ("%x:%u disconnected.\n",
                            event.peer -> address.host,
                            event.peer -> address.port);
                    break;
            }
        }
    }
}

Server::~Server()
{
    enet_host_destroy(server);
}