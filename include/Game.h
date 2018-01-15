#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "Config.h"
#include "CellVector.h"
#include "Window.h"

class Game
{
public:
    Game(Config& config, const char* gameTitle);

    // Generates the starting conditions for the cell vector based on the chosen seed
    void generateSeed(Seed seed);
    void generateSeed(double isAliveChance);

    bool wasEventTriggered(SDL_EventType eventType);
    void tick();
    void render();
    void delay(Uint32 msDelay);

private:
    CellVector cellVector;
    Window window;
};

#endif // !GAME_H