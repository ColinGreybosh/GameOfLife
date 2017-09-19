#include <SDL.h>
#include <iostream>

#include "../include/Game.h"

int main(int argc, char* args[])
{
    const char* GAME_TITLE = "Conway's Game of Life";

    const char* CONFIG_FILE_NAME = "config.ini";
    const char* CONFIG_REGEX = "(.*?)=\\s*(.*)";

    Config config(CONFIG_FILE_NAME, CONFIG_REGEX);
    /*
    Game game(config, GAME_TITLE);
    game.generateSeed(std::stof(config.getConfigValue("IS_ALIVE_CHANCE")));

    bool running = true;
    while (running)
    {
        running = !game.wasEventTriggered(SDL_QUIT);
        game.render();
        game.tick();
        game.delay(static_cast<Uint32>(16));
    }
    */

    std::cout << config.getConfigValue("PREFERRED_FPS");
    getchar();
    return 0;
}