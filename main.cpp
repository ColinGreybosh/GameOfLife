#include <SDL.h>
#include "Game.h"

int main(int argc, char* args[])
{
    // Configuration Settings //
    const int worldWidth   = 160;
    const int worldHeight  = 90;
    const double windowScale = 10.0; // Window size as a percentage of the world size. Ex: 50x50 world with 2.0 scale = 100x100 window
    const double isAliveChance = 0.5; // Percentage chance that a specific cell will be alive at world generation if RANDOM is the arg in CellVector.generateseed()  
    const char* gameTitle = "Conway's Game of Life";

    Game game(worldWidth, worldHeight, windowScale, gameTitle);
    game.generateSeed(RANDOM, isAliveChance);

    bool running = true;
    while (running)
    {
        // Check if the X button on the window was clicked, stop looping if so
        running = !game.wasEventTriggered(SDL_QUIT);
        // Render the cell vector on the SDL window
        game.render();
        // Calculate one generation of The Game of Life
        game.tick();
        // Crude delay system for the moment
        game.delay(static_cast<Uint32>(16));
    }

    return 0;
}