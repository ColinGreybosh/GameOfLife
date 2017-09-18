#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <iostream>

class Window
{
public:
    Window(int worldHeight, int worldWidth, double windowScale, const char* gameTitle);
    ~Window();
    
    bool wasEventTriggered(SDL_EventType eventType);
    void render2DBoolVector(const std::vector<std::vector<bool>> &boolVector);

private:
    int worldHeight, worldWidth, windowHeight, windowWidth;
    double windowScale;
    const char* gameTitle;
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool init();
    void close();

    int getWindowHeight();
    int getWindowWidth();
};

#endif //!WINDOW_H