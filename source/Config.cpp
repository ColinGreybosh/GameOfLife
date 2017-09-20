#include <SDL.h>
#include <string>
#include <fstream>
#include <regex>
#include <iostream>

#include "../include/Config.h"

Config::Config(const std::string fileName, const std::string regex) :
    configRegex(regex)
{
    this->fileName = fileName;
    regexString = regex;

    configFile.open(fileName, std::fstream::in);

    if (configFile.is_open())
    {
        std::string stringToParse;

        while (std::getline(configFile, stringToParse)) 
        {
            std::smatch matches;
            if (std::regex_search(stringToParse, matches, configRegex))
            {
                configOptions[matches[1].str()] = matches[2].str();
            }
            else
            {
                continue;
            }           
        }

        if (configOptions.size() != 5)
        {
            SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_ERROR,
                "Configuration Error",
                "Could not read all config file settings! Using default settings...",
                NULL);
            initWithDefault();
        }
    }
    else
    {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Configuration Error",
            "Could not open configuration file! Using default settings...",
            NULL);
        initWithDefault();
    }
}

Config::~Config()
{
    configFile.close();
}

std::string Config::getRegex()
{
    return regexString;
}

std::string Config::getFileName()
{
    return fileName;
}

std::string Config::getConfigValue(std::string key)
{
    // TODO: Fix the string returns
    return configOptions.find(key)->second;
}

void Config::initWithDefault()
{
    configOptions["WORLD_WIDTH"] = "200";
    configOptions["WORLD_HEIGHT"] = "200";
    configOptions["PREFERRED_FPS"] = "60";
    configOptions["WINDOW_SCALE"] = "3.0";
    configOptions["IS_ALIVE_CHANCE"] = "0.5";
}