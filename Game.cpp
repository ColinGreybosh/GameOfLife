#include "Game.h"
#include "CellVector.h"
#include "Window.h"

Game::Game(int worldWidth, int worldHeight, double windowScale, const char* gameTitle) 
    : cellVector(worldWidth, worldHeight), 
      window(worldWidth, worldHeight, windowScale, gameTitle)
{
    
}

void Game::generateSeed(Seed seed)
{
    cellVector.generateSeed(seed);
}

void Game::generateSeed(Seed seed, double isAliveChance)
{
    cellVector.generateSeed(seed, isAliveChance);
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