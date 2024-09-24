//
// Created by matthewperiut on 5/7/21.
//

#include "Native.h"
#include "Settings.h"
#include "Resolution.h"
#include <iostream>
#include <string>
#include <fstream>

Settings::Settings(std::string file)
{
    resolution = vi2d(NATIVESCREENWIDTH, NATIVESCREENHEIGHT);

    std::ifstream mySettingsFile(file);
    std::string output;
    while(mySettingsFile >> output)
    {
        if(output == "fullscreen")
        {
            mySettingsFile >> fullscreen;
        }
        if(output == "resolution")
        {
            mySettingsFile >> resolution.x >> resolution.y;
            resolution = ConvertToHeight(resolution, scale);
        }
        if(output == "vsync")
        {
            mySettingsFile >> vsync;
        }
    }
    if (fullscreen)
    {
        resolution = GetResolution();
    }
}