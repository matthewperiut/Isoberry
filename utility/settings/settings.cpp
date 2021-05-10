//
// Created by matthewperiut on 5/7/21.
//

#include "native.h"
#include "settings.h"
#include "resolution.h"

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