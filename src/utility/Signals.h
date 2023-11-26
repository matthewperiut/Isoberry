//
// Created by Matthew Periut on 9/29/21.
//

#pragma once

#include <csignal>

#include "../network/server/Server.h"

void abort(int signum);
void abortServer(int signum);

extern Server* globalServerPointer;