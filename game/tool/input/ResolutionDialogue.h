//
// Created by matthewperiut on 5/12/21.
//

#pragma once
#include "NumberTextBox.h"
class ResolutionDialogue
{
private:
    olc::vi2d textPosition{ 20,0 };
    bool CurrentlyDialoging = false;
    int step = 0;
    NumberTextBox width;
    NumberTextBox height;
public:
    ResolutionDialogue();
    void handle(olc::PixelGameEngine& g);

    void UpdateFile();
};