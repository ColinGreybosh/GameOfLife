#include <vector>
#include <cmath>

#include "Window.h"


Window::Window(int worldHeight, int worldWidth, double windowScale, const char* worldTitle)
{
    this->worldTitle = worldTitle;
    this->worldHeight = windowHeight = worldHeight;
    this->worldWidth = windowWidth = worldWidth;
    static_cast<int>(ceil(windowHeight *= windowScale));
    static_cast<int>(ceil(windowWidth *= windowScale));
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

void Window::render2DBoolVector(std::vector<std::vector<bool>> boolVector)
{
    std::cout << "Rendering cell vector...\n";
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    int vectorWidth = boolVector.size();
    int vectorHeight = boolVector[0].size();

    for (int x = 0; x < vectorWidth; x++)
    {
        for (int y = 0; y < vectorHeight; y++)
        {
            // Renderer draws in black if the cell is alive, white if it is dead
            (boolVector[x][y]) ? SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) 
                               : SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Rect cell;

            cell.x = static_cast<int>(ceil(x * (windowWidth / vectorWidth)));
            cell.w = static_cast<int>(ceil(windowWidth / vectorWidth));

            cell.y = static_cast<int>(ceil(y * (windowHeight / vectorHeight)));
            cell.h = static_cast<int>(ceil(windowHeight / vectorHeight));

            SDL_RenderFillRect(renderer, &cell);
        }
    }

    SDL_RenderPresent(renderer);
    std::cout << "Cell vector rendered...\n";
}

bool Window::initSDL()
{
    bool success = true;

    std::cout << "Initializing SDL...\n";
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
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

void Window::closeSDL()
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