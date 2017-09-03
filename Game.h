#ifndef GAME_H
#define GAME_H

#include "SDL.h"

#include "CellVector.h"
#include "Window.h"

class Game
{
public:
    Game(int width, int height, double windowScale, const char* gameTitle);

    // Generates the starting conditions for the cell vector based on the chosen seed
    void generateSeed(Seed seed);
    // Generates the starting conditions for the cell vector based on the chosen seed
    void generateSeed(double isAliveChance);
    // Checks if a certain SDL event was triggered and returns true if so
    bool wasEventTriggered(SDL_EventType eventType);
    // Updates the boolean values of each cell based on the rules for Conway's Game of Life
    void tick();
    // Prints the boolean contents of the 2D-vector argument to the console
    void render();
    // Delays SDL by the given amount of milliseconds
    void delay(Uint32 msDelay);

private:
    CellVector cellVector;
    Window window;
};

#endif // !GAME_H