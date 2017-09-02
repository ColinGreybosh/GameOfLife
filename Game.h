#ifndef GAME_H
#define GAME_H

#include "SDL.h"

#include "CellVector.h"
#include "Window.h"

class Game
{
public:
    Game(int width, int height, double windowScale, const char* gameTitle);

    void generateSeed(Seed seed);
    void generateSeed(Seed seed, double isAliveChance);
    bool wasEventTriggered(SDL_EventType eventType);
    void tick();
    void render();
    void delay(Uint32 msDelay);

private:
    CellVector cellVector;
    Window window;
};

#endif // !GAME_H