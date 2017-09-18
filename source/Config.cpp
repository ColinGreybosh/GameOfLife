#include <SDL.h>
#include <string>
#include <fstream>
#include <regex>

#include "../include/Config.h"

Config::Config(const std::string fileName, const std::string regex) :
    configRegex(regex)
{
    this->fileName = fileName;
    regexString = regex;

    configFile.open(fileName);

    if (configFile.is_open())
    {
        // TODO: Add config values to map
    }
    else
    {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Configuration Error",
            "Could not open configuration file!",
            NULL);
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

mapDataTypes Config::getConfigValue(std::string key)
{
    return configOptions[key];
}