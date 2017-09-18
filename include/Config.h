#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>
#include <map>
#include <regex>

struct mapDataTypes
{
    int i;
    double d;
    std::string str;
};

class Config
{
public:
    Config(const std::string fileName, const std::string regex);
    ~Config();

    std::string getRegex();
    std::string getFileName();
    mapDataTypes getConfigValue(std::string key);

private:
    std::string fileName;
    std::ifstream configFile;

    std::string regexString;
    std::regex configRegex;
    std::smatch regexMatch;

    std::map<std::string, mapDataTypes> configOptions;
};

#endif // !CONFIG_H