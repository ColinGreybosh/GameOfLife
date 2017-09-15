#include <vector>
#include <cmath>
#include <SDL.h>

#include "../include/Window.h"


Window::Window(int worldWidth, int worldHeight, double windowScale, const char* worldTitle)
{
    this->worldTitle = worldTitle;
    this->worldWidth = windowWidth = worldWidth;
    this->worldHeight = windowHeight = worldHeight;
    static_cast<int>(ceil(windowWidth *= windowScale));
    static_cast<int>(ceil(windowHeight *= windowScale));
    // Initialize SDL and throw a runtime error if it fails
    if (!init())
    {
        close();
    }
    SDL_RenderSetScale(renderer, windowScale, windowScale);
}

Window::~Window()
{
    close();
}

bool Window::wasEventTriggered(SDL_EventType eventType)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    
    return (eventType == event.type) ? true : false;
}

void Window::render2DBoolVector(const std::vector<std::vector<bool>> &boolVector)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black

    const int vectorWidth = boolVector.size();
    const int vectorHeight = boolVector[0].size();

    for (int x = 0; x < vectorWidth; x++)
    {
        for (int y = 0; y < vectorHeight; y++)
        {
            // Renderer fills a black rectangle if the cell is alive
            if (boolVector[x][y])
            {
                SDL_Rect cell{x, y, 1, 1};
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

bool Window::init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_EVENTS) == 0)
    {
        window = SDL_CreateWindow(
            worldTitle, 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED,
            windowWidth, 
            windowHeight, 
            SDL_WINDOW_SHOWN);

        if (!window)
        {
            success = false;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        else
        {
            success = false;
        }
    }
    else
    {
        success = false;
    }

    return success;
}

void Window::close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int Window::getWindowHeight()
{
    return windowHeight;
}

int Window::getWindowWidth()
{
    return windowWidth;
}