//
// Created by Matthew Periut on 5/11/21.
//

#pragma once

#include "../../../header/olcPixelGameEngine.h"
#include <string>

class NumberTextBox
{
private:
    std::string input;
public:
    olc::vi2d position{ 20,20 };

    void DrawInput(olc::PixelGameEngine& g);
    bool ListenForInput(olc::PixelGameEngine& g);
    int GetInput();
};