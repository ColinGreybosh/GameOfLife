#include "../include/Game.h"
#include "../include/Config.h"
#include "../include/CellVector.h"
#include "../include/Window.h"

Game::Game(int worldWidth, int worldHeight, double windowScale, char* gameTitle, char* configFileName, char* configRegex) 
    : config(configFileName, configRegex),
      cellVector(worldWidth, worldHeight), 
      window(worldWidth, worldHeight, windowScale, gameTitle){}

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