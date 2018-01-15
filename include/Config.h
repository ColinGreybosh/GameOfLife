#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>
#include <map>
#include <regex>
#include <type_traits>

class Config
{
public:
    Config(const std::string fileName, 
           const std::string regex, 
           const std::map<std::string, std::string> configOptionsDefault);
    ~Config();

    // Returns a string containing the Regular Expression used to parse the config file
    std::string getRegex();

    // Returns a string containing the relative name of the config file
    std::string getFileName();

    // Returns a string value related to the passed argument string key
    template <typename T>
    inline typename std::enable_if<std::is_same<T, int>::value, int>::type
    getConfigValue(const std::string key)
    {
        return std::stoi(configOptions.find(key)->second);
    }
    
    // Returns a string value related to the passed argument string key
    template <typename T>
    inline typename std::enable_if<std::is_same<T, double>::value, double>::type
    getConfigValue(const std::string key)
    {
        return std::stof(configOptions.find(key)->second);
    }

private:
    std::string fileName;
    std::ifstream configFile;
    std::string regexString;
    std::regex configRegex;
    std::map<std::string, std::string> configOptions;
    std::map<std::string, std::string> configOptionsDefault;

    bool configKeysAreVerified();

    void initWithDefault();
    void handleConfigReadError();
};

#endif // !CONFIG_H