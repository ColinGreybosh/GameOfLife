#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <iostream>

class Window
{
public:
    Window(int worldHeight, int worldWidth, double windowScale, const char* worldTitle);

    // Returns the height of the SDL window
    int getWindowHeight();
    // Returns the width of the SDL window
    int getWindowWidth();
    // Checks if a certain SDL event was triggered and returns true if so
    bool wasEventTriggered(SDL_EventType eventType);
    // Prints the boolean contents of the 2D-vector argument to the console
    void render2DBoolVector(std::vector<std::vector<bool>> boolVector);
    // Initializes SDL, the SDL window, and the SDL renderer
    bool initSDL();
    // Deallocates and destroys all SDL variables and windows
    void closeSDL();

private:
    int worldHeight, worldWidth, windowHeight, windowWidth;
    double windowScale;
    const char* worldTitle;
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif