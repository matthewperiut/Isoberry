//
// Created by Matthew Periut on 5/11/21.
//

#include "NumberTextBox.h"

using namespace olc;

bool NumberTextBox::ListenForInput(olc::PixelGameEngine &g)
{
    static olc::Key numbers[10] =
    { olc::Key::K0,
      olc::Key::K1,
      olc::Key::K2,
      olc::Key::K3,
      olc::Key::K4,
      olc::Key::K5,
      olc::Key::K6,
      olc::Key::K7,
      olc::Key::K8,
      olc::Key::K9
      };
    for(int i = 0; i < 10; i++)
    {
        if(g.GetKey(numbers[i]).bPressed)
        {
            if(input.length() < 9)
                input += std::to_string(i);
        }
    }
    if(g.GetKey(olc::Key::BACK).bPressed)
    {
        if(!input.empty())
            input.pop_back();
    }
    if(g.GetKey(olc::Key::ENTER).bPressed)
    {
        return true;
    }
    return false;
}

int NumberTextBox::GetInput() {
    return std::stoi(input);
}

void NumberTextBox::DrawInput(olc::PixelGameEngine &g)
{
    g.DrawStringDecal(position, input);
}
