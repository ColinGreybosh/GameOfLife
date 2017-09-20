#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>
#include <map>
#include <regex>

class Config
{
public:
    Config(const std::string fileName, const std::string regex);
    ~Config();

    // Returns a string containing the Regular Expression used to parse the config file
    std::string getRegex();
    // Returns a string containing the relative name of the config file
    std::string getFileName();
    // Returns a string value related to the passed argument string key
    std::string getConfigValue(std::string key);

private:
    std::string fileName;
    std::ifstream configFile;
    std::string regexString;
    std::regex configRegex;
    std::map<std::string, std::string> configOptions;

    void initWithDefault();
};

#endif // !CONFIG_H