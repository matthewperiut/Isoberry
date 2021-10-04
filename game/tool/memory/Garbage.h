//
// Created by matthewperiut on 10/4/21.
//

#pragma once

#include <vector>

class Garbage
{
public:
    std::vector<void*> sprites;
    std::vector<void*> decals;

    void DeleteAll();
};
