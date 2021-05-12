//
// Created by matthewperiut on 5/7/21.
//

#pragma once

#include "../../header/olcPixelGameEngine.h"
#include <iostream>
#include <string>
#include <fstream>

class Settings
{
public:
    Settings(std::string file);
    bool vsync{ true };
    bool fullscreen{ false };

    int scale{ 3 };
    olc::vi2d resolution{0,0};
};