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
    Config(const std::string fileName);
    ~Config();

    mapDataTypes getValue(std::string key);

private:
    std::regex configRegex;
    std::ifstream configFile;
    std::map<std::string, mapDataTypes> configOptions;
};

#endif // !CONFIG_H