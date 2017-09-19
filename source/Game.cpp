#include "../include/Game.h"
#include "../include/Config.h"
#include "../include/CellVector.h"
#include "../include/Window.h"

Game::Game(Config& config, const char* gameTitle) :
    cellVector(
        std::stoi(config.getConfigValue("WORLD_WIDTH")), 
        std::stoi(config.getConfigValue("WORLD_HEIGHT"))),
    window(
        std::stoi(config.getConfigValue("WORLD_WIDTH")), 
        std::stoi(config.getConfigValue("WORLD_HEIGHT")), 
        std::stof(config.getConfigValue("WINDOW_SCALE")), 
        gameTitle)
{}

void Game::generateSeed(Seed seed)
{
    cellVector.generateSeed(seed);
}

void Game::generateSeed(double isAliveChance)
{
    cellVector.generateSeed(isAliveChance);
}

bool Game::wasEventTriggered(SDL_EventType eventType)
{
    return window.wasEventTriggered(eventType);
}

void Game::tick()
{
    cellVector.tick();
}

void Game::render()
{
    window.render2DBoolVector(cellVector.getCellVector());
}

void Game::delay(Uint32 msDelay)
{
    SDL_Delay(msDelay);
}