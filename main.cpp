#include <string>

#include "CellVector.h"
#include "Window.h"

int main(int argc, char* args[])
{
    // Configuration Settings //
    int worldWidth   = 200;
    int worldHeight  = 200;
    // Window size as a percentage of the world size. EX: 50x50 world with 2.0 scale = 100x100 window
    double windowScale = 5;                            
    // Percentage chance that a specific cell will be alive at world generation if RANDOM is the arg in CellVector.generateseed()
    double isAliveChance = 0.5;                        
    // Name of the program window
    const char* gameTitle = "Conway's Game of Life";   

    // Initialize cell vector
    CellVector cellVector(worldHeight, worldWidth, isAliveChance);
    // Generate seed for cell vector frpm given seed type
    cellVector.generateSeed(RANDOM);

    // Initialize the window class
    Window window(worldWidth, worldHeight, windowScale, "Conway's Game of Life");

    // Initialize SDL within the window class
    bool running = window.initSDL();

    while (running)
    {
        // Check if the X button on the window was clicked, stop looping if so
        running = (window.wasEventTriggered(SDL_QUIT)) ? false : true;

        // Render the cell vector on the SDL window
        window.render2DBoolVector(cellVector.getCellVector());

        // Calculate one generation of The Game of Life
        cellVector.tick();

        // Crude delay system for the moment
        SDL_Delay(static_cast<Uint32>(1 / 60 * 1e4));
    }

    // Deallocate and destroy all SDL variables and windows
    window.closeSDL();

    return 0;
}