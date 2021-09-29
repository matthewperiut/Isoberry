//
// Created by matthewperiut on 9/29/21.
//

#include "Client.h"

Client::Client()
{
    client = enet_host_create(nullptr, 1, 1, 0, 0);

    if(client == nullptr)
    {
        fprintf(stderr, "An error occurred while trying to create an ENet client host");
        exit(EXIT_FAILURE);
    }

    //enet_address_set_host(&address, "73.137.115.94");
    enet_address_set_host(&address, "10.0.0.11");
    address.port = 47623; // ISOBE as phone number

    peer = enet_host_connect(client, &address, 1, 0);
    if(peer == nullptr)
    {
        fprintf(stderr, "No Server\n");
        exit(EXIT_FAILURE);
    }

    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
    {
        puts("Connection to Server successful.");
    }
    else
    {
        enet_peer_reset(peer);
        puts("Connection to Server failed.");
        exit(EXIT_FAILURE);
    }
}

void Client::Run()
{
    while(running)
    {
        while(enet_host_service(client, &event, 1000) > 0)
        {
            switch(event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    printf ("A packet of length %zu containing %s was received from %x:%u on channel %u.\n",
                            event.packet -> dataLength,
                            event.packet -> data,
                            event.peer -> address.host,
                            event.peer -> address.port,
                            event.channelID);
                    /* Clean up the packet now that we're done using it. */
                    enet_packet_destroy (event.packet);
                    break;
                case ENET_EVENT_TYPE_NONE:
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    break;
            }
        }
    }
}

Client::~Client()
{
    enet_peer_disconnect(peer, 0);

    while(enet_host_service(client, &event, 3000))
    {
        switch(event.type)
        {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Disconnection successful");
                break;
        }
    }
}