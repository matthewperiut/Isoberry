//
// Created by matthewperiut on 9/29/21.
//

#include "Client.h"

Client::Client()
{

}

void Client::SetLevel(Level& level)
{
    clientBundle->level = &level;
    players = &clientBundle->level->players;
}

void Client::SendPlayerData()
{
    Player& p = *clientBundle->localPlayer;

    // all in float
    // Format: x, y, z, vx, vy, vz
    int bytes = (6 * sizeof(float));
    float *data = (float*)malloc(bytes);

    data[0] = p.position.x;
    data[1] = p.position.y;
    data[2] = p.position.z;
    data[3] = p.velocity.x;
    data[4] = p.velocity.y;
    data[5] = p.velocity.z;

    ENetPacket * packet = enet_packet_create (data, bytes, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (peer, 0, packet);

    free(data);
}

int Client::GetPlayerIndex(int id)
{
    for(int i = 0; i < (*players).size(); i++)
    {
        if((*players)[i].id == id)
            return i;
    }
    return -1;
}

void Client::HandleID(ENetEvent& ev)
{
    if (ev.packet->dataLength != 1)
        return;

    uint8_t id = *ev.packet->data;

    if(id == clientBundle->localPlayer->id)
        return;

    if (clientBundle->localPlayer->id == -1)
    {
        clientBundle->localPlayer->id = id;
        std::cout << "I am " << int(id) << std::endl;
        return;
    }

    int index = GetPlayerIndex(id);
    if(index == -1)
    {
        index = (*players).size();
        (*players).emplace_back(v3(8,23,8), clientBundle->level->DOS);
        (*players)[index].id = id;

    }
    else
    {
        std::cout << index << " is leaving.\n";
        (*players)[index].eraseMe = true;
    }
}

void Client::HandlePositions(ENetEvent& ev)
{
    if(ev.packet->dataLength % 7 != 0 || ev.packet->dataLength < 6)
        return;

    float* data = reinterpret_cast<float *>(ev.packet->data);

    for(int i = 0; i < players->size(); i++)
    {
        int index = i*7;

        if(data[index] == clientBundle->localPlayer->id)
            continue;

        (*players)[index].position = v3(data[index+1],data[index+2],data[index+3]);
        (*players)[index].velocity = v3(data[index+4],data[index+5],data[index+6]);
    }
}

void Client::Run()
{
    client = enet_host_create(nullptr, 1, 2, 0, 0);

    if(client == nullptr)
    {
        std::cerr << "An error occurred while trying to create an ENet client host" << std::endl;
        return;
    }

    enet_address_set_host(&address, "127.0.0.1");
    address.port = 47623; // I S O B E

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
        while(enet_host_service(client, &event, 50) > 0)
        {
            switch(event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    HandleID(event);
                    HandlePositions(event);
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

    SetLevel(*clientBundle.level);

    clientThread = std::thread(&Client::Run, this);
}
