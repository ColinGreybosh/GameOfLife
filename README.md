# Game of Life

A C++ implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) using the SDL2 library for rendering.

## Table of Contents

- [Dependencies](#dependencies) 
- [Usage](#usage)  
- [Stack Exchange](#stack-exchange)
- [To-do](#to-do)

## Dependencies

- [SDL2](https://www.libsdl.org/download-2.0.php)

## Usage

1. Edit `config.ini` to preferred game and display settings.
```
[DISPLAY]                   |  Sets the window resolution and framerate
PREFERRED_FPS = 60          |  Currently unused
WINDOW_SCALE = 5            |  Window resolution is equal to this float times the world width/height
                            |
[GAME OPTIONS]              |  Sets the size of the game area and how populated it is
WORLD_WIDTH = 100           |  Width of the vector containing the cells
WORLD_HEIGHT = 100          |  Height of the vector containing the cells
IS_ALIVE_CHANCE = 0.444444  |  Chance a cell will be alive (0 = no cells, 1 = all cells)
```
2. Run ConwaysGameOfLife.exe

## Stack Exchange

- [Code Review](https://codereview.stackexchange.com/questions/174619/c-implementation-of-conways-game-of-life-with-sdl2)

## To-do

- ~~Create a `Config` class that can read (key, value) pairs from a text file and apply them to the `const` variables defined in `int main()`.~~
- Add keyboard and mouse interaction.
  - Press `R` to reset world.
  - Left click on the window to spawn living cells.
- Add dynamic FPS for `PREFERRED_FPS` option.
