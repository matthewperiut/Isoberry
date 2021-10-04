//
// Created by matthewperiut on 9/27/21.
//

#include "Server.h"
#include "../../../utility/Signals.h"

Server::Server()
{
    // Handling ABORT
    globalServerPointer = this;
    signal(SIGABRT, abortServer);

    serverThread = std::thread(&Server::Run, this);

    levels.emplace_back();
    levels[0].LoadFromFile(GetAssetPath() + "levels/basis.txt", false);
    players = &levels[0].players;

    if(gui.Construct(256,144,4,4,false,true))
        gui.Start();
}

int Server::GetPlayerIndex(ENetPeer* peer)
{
    for(int i = 0; i < (*players).size(); i++)
    {
        if((*players)[i].host == peer->address.host)
            if((*players)[i].port == peer->address.port)
                return i;
    }
    return -1;
}

void Server::SendByte(ENetEvent& ev, uint8_t data, uint8_t channel, bool toAll)
{
    ENetPacket* packet = enet_packet_create(&data, 1, ENET_PACKET_FLAG_RELIABLE);
    if(toAll)
    {
        enet_host_broadcast(server, 0, packet);
    }
    else
    {
        enet_peer_send(ev.peer, 0, packet);
    }
}

void Server::AddPlayer(ENetEvent& ev)
{
    static uint8_t id = -1;
    id++;

    int index = (*players).size();
    (*players).emplace_back(v3(8,23,8),levels[0].DOS);
    (*players)[index].id = id;
    (*players)[index].host = ev.peer->address.host;
    (*players)[index].port = ev.peer->address.port;
    (*players)[index].peer = ev.peer;

    gui.InsertMessage(std::to_string(id) + " joined.");

    // Tell everyone about this player joining, also tell the player their ID
    SendByte(ev, id, 0,true);

    // Tell the player about other (*players) on the server
    for(int i = 0; i < (*players).size(); i++)
    {
        if((*players)[i].id == id)
            continue;
        SendByte(ev, (*players)[i].id, 0, false);
    }
}

void Server::RemovePlayer(ENetEvent& ev)
{
    int index = GetPlayerIndex(ev.peer);
    gui.InsertMessage(std::to_string((*players)[index].id) + " left.");

    // Tell everyone the player is leaving
    SendByte(ev, (*players)[index].id, 0, true);

    (*players).erase((*players).begin() + index);
}

void Server::HandlePlayerPosition(ENetEvent& ev)
{
    if(ev.packet->dataLength != 24)
        return;

    // Receive and store player data
    int index = GetPlayerIndex(ev.peer);
    Player& p = (*players)[index];
    float* d = reinterpret_cast<float *>(ev.packet->data);

    p.position = v3(d[0],d[1],d[2]);
    p.velocity = v3(d[3],d[4],d[5]);

    // Send back other people's data
    int it = 0; // it for iterator
    float data[1024];

    for(int i = 0; i < (*players).size(); i++)
    {
        data[it] = (*players)[i].id;
        v3& pos = (*players)[i].position;
        data[it+1] = (pos.x);
        data[it+2] = (pos.y);
        data[it+3] = (pos.z);
        v3& vel = (*players)[i].velocity;
        data[it+4] = (vel.x);
        data[it+5] = (vel.y);
        data[it+6] = (vel.z);
        it += 7;
    }

    ENetPacket* packet = enet_packet_create(data,(*players).size()*7*sizeof(float),ENET_PACKET_FLAG_RELIABLE);
    //enet_host_broadcast(server,ENET_PACKET_FLAG_RELIABLE,packet);
    enet_peer_send(ev.peer, 0, packet);
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
        while(enet_host_service(server, &event, 10) > 0)
        {
            switch(event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                    AddPlayer(event);
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    HandlePlayerPosition(event);
                    break;
                case ENET_EVENT_TYPE_NONE:
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    RemovePlayer(event);
                    break;
            }
        }
    }
    gui.InsertMessage("Stopping Server...");
}

Server::~Server()
{
    running = false;
    serverThread.join();
    enet_host_destroy(server);
}