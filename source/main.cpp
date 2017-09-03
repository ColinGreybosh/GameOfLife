#include "SDL.h"
#include "../include/Game.h"

int main(int argc, char* args[])
{
    // Configuration Settings //
    const int worldWidth   = 160;
    const int worldHeight  = 90;
    const double windowScale = 10.0; // Window size as a percentage of the world size. Ex: 50x50 world with 2.0 scale = 100x100 window
    const double isAliveChance = 0.5; // Percentage chance that a specific cell will be alive at world generation if RANDOM is the arg in CellVector.generateseed()  
    const char* gameTitle = "Conway's Game of Life";

    Game game(worldWidth, worldHeight, windowScale, gameTitle);
    game.generateSeed(isAliveChance);

    bool running = true;
    while (running)
    {
        running = !game.wasEventTriggered(SDL_QUIT);
        game.render();
        game.tick();
        game.delay(static_cast<Uint32>(16));
    }

    return 0;
}