#include <SDL.h>
#include <string>
#include <fstream>
#include <regex>
#include <iostream>

#include "../include/Config.h"

Config::Config(const std::string fileName, const std::string regex, const std::map<std::string, std::string> configOptionsDefault) :
    configRegex(regex)
{
    this->fileName = fileName;
    this->configOptionsDefault = configOptionsDefault;
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

        if (!configKeysAreVerified())
        {
            handleConfigReadError();
        }
    }
    else
    {
        handleConfigReadError();
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

bool Config::configKeysAreVerified()
{
    if (configOptions.size() != configOptionsDefault.size())
    {
        return false;
    }

    for (auto& configPair : configOptions)
    {
        if (configOptionsDefault.find(configPair.first) == configOptionsDefault.end())
        {
            return false;
        }
    }

    return true;
}

void Config::initWithDefault()
{
    configOptions.swap(configOptionsDefault);
}

void Config::handleConfigReadError()
{
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR,
        "Configuration Error",
        "Could not read config file settings! Using default settings...",
        NULL);

    initWithDefault();
}
