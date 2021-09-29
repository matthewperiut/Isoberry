//
// Created by Matthew Periut on 9/29/21.
//

#pragma once

#include "../../../header/olcPixelGameEngine.h"

class ServerGUI : public olc::PixelGameEngine
{
private:
    bool* running;
    const int countDownMax = 120;
    int countDown = 0;
public:
    ServerGUI(bool& running);
public:
    std::vector<std::string> messages;

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserDestroy() override;

    void InsertMessage(std::string text);
};

