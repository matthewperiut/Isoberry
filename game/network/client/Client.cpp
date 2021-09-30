//
// Created by matthewperiut on 9/29/21.
//

#include "Client.h"

Client::Client()
{

}

void Client::SendPlayerData()
{
    Player& p = *clientBundle->localPlayer;

    // all in float_t
    // Format: x, y, z, vx, vy, vz
    int bytes = (6 * sizeof(float_t));
    float_t *data = (float_t*)malloc(bytes);

    std::cout << bytes << std::endl;

    data[0] = p.GetPositionRef().x;
    data[1] = p.GetPositionRef().y;
    data[2] = p.GetPositionRef().z;
    data[3] = p.velocity.x;
    data[4] = p.velocity.y;
    data[5] = p.velocity.z;

    ENetPacket * packet = enet_packet_create (data, bytes, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (peer, 0, packet);

    free(data);
}

void Client::Run()
{
    client = enet_host_create(nullptr, 1, 2, 0, 0);

    if(client == nullptr)
    {
        std::cerr << "An error occurred while trying to create an ENet client host" << std::endl;
        return;
    }

    //enet_address_set_host(&address, "73.137.115.94");
    enet_address_set_host(&address, "10.0.0.11");
    address.port = 47623; // ISOBE as phone number

    peer = enet_host_connect(client, &address, 1, 0);
    if(peer == nullptr)
    {
        std::cerr << "No Server" << std::endl;
        running = false;
    }

    if (enet_host_service(client, &event, 2000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
    {
        std::cout << "Connection to Server successful." << std::endl;
        connected = true;
    }
    else
    {
        enet_peer_reset(peer);
        std::cout << "Connection to Server failed." << std::endl;
        running = false;
    }

    while(running)
    {
        SendPlayerData();
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
    if(connected)
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
                        std::cout << "Disconnection successful" << std::endl;
                        break;
            }
        }
    }
}

void Client::StartThread(ClientBundle &clientBundle)
{
    clientBundle.running = &running;
    this->clientBundle = &clientBundle;
    clientThread = std::thread(&Client::Run, this);
}
