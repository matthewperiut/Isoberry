//
// Created by matthewperiut on 5/12/21.
//

#include "Replace.h"
#include "../../utility/AssetPath.h"
#include <fstream>
#include <sstream>
#include <filesystem>

void FindReplaceLine(std::string path, std::string keyword, std::string newLine)
{
    bool foundOriginal = false;
    std::string totalOutput;
    std::ifstream file(path);

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string test;
        iss >> test;
        if(test == keyword)//"resolution")
        {
            foundOriginal = true;
            totalOutput += newLine;//"resolution " + std::to_string(width.GetInput()) + " " + std::to_string(height.GetInput());
        }
        else
        {
            totalOutput += test;
            std::string info;
            while(iss >> info)
            {
                totalOutput += " " + info;
            }
        }
        totalOutput += '\n';
    }
    if(!foundOriginal)
    {
        totalOutput += newLine;
    }
    file.close();
    std::ofstream outfile(path);
    outfile << totalOutput;
    outfile.close();
}

void HandleUpdateSetting(std::string keyword, std::string newLine)
{
    std::string path = GetAssetPath() + "settings.txt";
    if(std::filesystem::exists(path))
    {
        FindReplaceLine(path,keyword,newLine);
    }
    else
    {
        std::ofstream file(path);
        file << newLine;
        file.close();
    }
}