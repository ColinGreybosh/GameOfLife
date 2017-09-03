#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <iostream>

class Window
{
public:
    Window(int worldHeight, int worldWidth, double windowScale, const char* worldTitle);
    ~Window();
    
    bool wasEventTriggered(SDL_EventType eventType);
    void render2DBoolVector(const std::vector<std::vector<bool>> &boolVector);

private:
    int worldHeight, worldWidth, windowHeight, windowWidth;
    double windowScale;
    const char* worldTitle;
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Initializes SDL, the SDL window, and the SDL renderer
    bool init();
    // Deallocates and destroys all SDL variables and windows
    void close();

    int getWindowHeight();
    int getWindowWidth();
};

#endif //!WINDOW_H