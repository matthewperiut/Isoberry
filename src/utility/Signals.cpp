//
// Created by Matthew Periut on 9/29/21.
//

#include "../Game.h"
#include "Signals.h"

void abort(int signum)
{
    game.client.running = false;
    game.client.clientThread.join();
    exit(signum);
}

Server* globalServerPointer;
void abortServer(int signum)
{
    if(globalServerPointer != nullptr)
    {
        globalServerPointer->running = false;
        exit(signum);
    }
}