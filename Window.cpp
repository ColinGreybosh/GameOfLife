#include <vector>
#include <cmath>
#include <stdexcept>

#include "SDL.h"
#include "Window.h"


Window::Window(int worldHeight, int worldWidth, double windowScale, const char* worldTitle)
{
    this->worldTitle = worldTitle;
    this->worldWidth = windowWidth = worldWidth;
    this->worldHeight = windowHeight = worldHeight;
    static_cast<int>(ceil(windowHeight *= windowScale));
    static_cast<int>(ceil(windowWidth *= windowScale));
    // Initialize SDL and throw a runtime error if it fails
    if (!init())
    {
        throw std::runtime_error("SDL could not initialize.");
        close();
    }
    SDL_RenderSetScale(renderer, windowScale, windowScale);
}

Window::~Window()
{
    close();
}

int Window::getWindowHeight()
{
    return windowHeight;
}

int Window::getWindowWidth()
{
    return windowWidth;
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
                SDL_Rect cell{ x, y, 1, 1 };
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

bool Window::init()
{
    bool success = true;

    std::cout << "Initializing SDL...\n";
    if (SDL_Init(SDL_INIT_EVENTS) == 0)
    {
        std::cout << "SDL initialized...\n";
        std::cout << "Creating window...\n";

        window = SDL_CreateWindow(worldTitle, 
                                  SDL_WINDOWPOS_UNDEFINED, 
                                  SDL_WINDOWPOS_UNDEFINED, 
                                  windowWidth, 
                                  windowHeight, 
                                  SDL_WINDOW_SHOWN);
        if (window)
        {
            std::cout << "Window created...\n";
        }
        else
        {
            std::cout << "Window could not be created. SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }

        std::cout << "Creating renderer...\n";

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created...\n";
        }
        else
        {
            std::cout << "Renderer could not be created. SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
    }
    else
    {
        std::cout << "SDL could not initialize. SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    return success;
}

void Window::close()
{
    SDL_DestroyWindow(window);
    if (window == NULL)
    {
        std::cout << "Window destroyed...";
    }
    SDL_DestroyRenderer(renderer);
    if (renderer == NULL)
    {
        std::cout << "Renderer destroyed...";
    }
    SDL_Quit();
}