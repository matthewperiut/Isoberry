//
// Created by matthewperiut on 5/12/21.
//

#include <fstream>
#include <iostream>
#include "Replace.h"
#include "ResolutionDialogue.h"
#include "../../../utility/assetPath.h"
#include "../../../utility/settings/native.h"

ResolutionDialogue::ResolutionDialogue()
{
    width.position = textPosition + olc::vi2d(0,8);
    height.position = textPosition + olc::vi2d(0,8);
}

void ResolutionDialogue::UpdateFile()
{
    std::string newLine = "resolution " + std::to_string(width.GetInput()) + " " + std::to_string(height.GetInput());
    HandleUpdateSetting("resolution",newLine);
}

void ResolutionDialogue::handle(olc::PixelGameEngine &g)
{
    if(g.GetKey(olc::Key::F1).bPressed)
    {
        CurrentlyDialoging = !CurrentlyDialoging;
        step = 0;
    }
    if(!CurrentlyDialoging)
        return;

    switch(step)
    {
        case 0:
            g.DrawStringDecal(textPosition, "Resolution Width:");
            break;
        case 1:
            g.DrawStringDecal(textPosition, "Resolution Height:");
            break;
        case 2:
            if(width.GetInput() < NATIVESCREENWIDTH || height.GetInput() < NATIVESCREENHEIGHT)
            {
                g.DrawStringDecal(textPosition, "Failed Resolution!");
            }
            else
            {
                g.DrawStringDecal(textPosition, "Resolution will update on reboot!");
            }

            g.DrawStringDecal(width.position, "Press ENTER to finish.");
            if(g.GetKey(olc::Key::ENTER).bPressed)
            {
                step = 0;
                CurrentlyDialoging = false;
                if(!(width.GetInput() < NATIVESCREENWIDTH) && !(height.GetInput() < NATIVESCREENHEIGHT)) {
                    UpdateFile();
                }
            }
            return;
    }
    NumberTextBox* current = step ? &height : &width;

    if(current->ListenForInput(g))
        step++;
    current->DrawInput(g);
}