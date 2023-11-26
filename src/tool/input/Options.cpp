//
// Created by matthewperiut on 5/12/21.
//

#include "Options.h"
#include "Replace.h"
#include "../../utility/settings/Settings.h"

extern Settings settings;

const static constexpr int showTime = 1;

void BooleanSettingToggle(std::string keyword, std::string &reply, bool &setting, float &elapsed, olc::PixelGameEngine& g, olc::Key k, int offset = 0)
{
    if(g.GetKey(k).bPressed)
    {
        setting = !setting;
        HandleUpdateSetting(keyword, keyword + " " + std::to_string(setting));
        reply = std::string(keyword + " is now " + (setting ? "on" : "off"));
        elapsed = 0;
    }

    if(elapsed < showTime)
    {
        olc::vi2d pos = olc::vi2d(20,30);
        g.DrawStringDecal(pos+olc::vi2d(0,-offset),reply);
        g.DrawStringDecal(pos + olc::vi2d(0,8), "Updates after restart");
    }
}

void VSyncToggle(olc::PixelGameEngine& g, float fElapsedTime, olc::Key k)
{
    static std::string reply;
    static float elapsed = showTime;
    elapsed += fElapsedTime;
    BooleanSettingToggle("vsync", reply, settings.vsync, elapsed, g, k);
}
void FullScreenToggle(olc::PixelGameEngine& g, float fElapsedTime, olc::Key k)
{
    static std::string reply;
    static float elapsed = showTime;
    elapsed += fElapsedTime;
    BooleanSettingToggle("fullscreen", reply, settings.vsync, elapsed, g, k, 8);
}
