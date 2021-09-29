//
// Created by Matthew Periut on 9/29/21.
//

#include "ServerGUI.h"

//
// Created by matthewperiut on 5/7/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION
#include "ServerGUI.h"

ServerGUI::ServerGUI(bool& running) : running{&running}
{
    sAppName = "Isoberry Server";
}

bool ServerGUI::OnUserCreate()
{
    return true;
}

bool ServerGUI::OnUserUpdate(float fElapsedTime)
{
    for(int y = 0; y < messages.size(); y++)
    {
        int actualY = y * 8;
        DrawStringDecal(olc::vf2d(0,actualY), messages.at(y), olc::WHITE);
    }
    if(GetKey(olc::Key::ESCAPE).bPressed)
    {
        *running = false;
    }
    if(!*running)
    {
        countDown++;
        if(countDown == countDownMax)
            return false;
    }
    return true;
}

bool ServerGUI::OnUserDestroy()
{
    return true;
}

void ServerGUI::InsertMessage(std::string text)
{
    messages.push_back(text);

    /* Multi-line later
    int charactersPerLine = (ScreenWidth()/8);
    int lines = text.length() % charactersPerLine;
    for(int i = 0; i < lines; i++)
    {
        int length = (1+i)*charactersPerLine;
        if(text.length() < (1+i)*charactersPerLine)
            length = text.length();
        messages.push_back(text.substr(i*charactersPerLine,length));
    }*/

    if(messages.size() > ScreenHeight()/8)
        messages.erase(messages.begin());
}