//
// Created by Matthew Periut on 5/11/21.
//

#include "assetPath.h"

#include <mach-o/dyld.h>

#ifdef __APPLE__
    std::string GetAssetPath()
    {
        static std::string pathStr;

        if (pathStr.empty())
        {
            char path[1024];
            uint32_t size = sizeof(path);
            if (_NSGetExecutablePath(path, &size) == 0)
                pathStr = path;
            else
                printf("buffer too small; need size %u\n", size);

            pathStr.erase(pathStr.begin()+pathStr.find("MacOS/Isoberry"), pathStr.end());
            pathStr += "assets/";
        }

        return pathStr;
    }
#endif
#ifdef _WIN32 || __linux__
    std::string GetAssetPath()
    {
        return "./assets/";
    }
#endif
