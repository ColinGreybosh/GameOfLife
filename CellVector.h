#ifndef CELLVECTOR_H
#define CELLVECTOR_H

#include <vector>

// Contains enum values for the game seeds created by CellVector::generateSeed()
enum Seed
{
    // Randomly generated, user-defined region
    RANDOM,

    /*
    Still Life, 4x4 region, 4 live cells
    ------------------------------------
    . . . .
    . 0 0 .
    . 0 0 .
    . . . .
    */
    BLOCK,

    /*
    Still Life, 6x5 region, 6 live cells
    ------------------------------------
    . . . . . .
    . . 0 0 . .
    . 0 . . 0 .
    . . 0 0 . .
    . . . . . .
    */
    BEEHIVE,

    /*
    Still Life, 6x6 region, 7 live cells
    ------------------------------------
    . . . . . .
    . . 0 0 . .
    . 0 . . 0 .
    . . 0 . 0 .
    . . . 0 . .
    . . . . . .
    */
    LOAF,

    /*
    Still Life, 5x5 region, 5 live cells
    ------------------------------------
    . . . . .
    . 0 0 . .
    . 0 . 0 .
    . . 0 . .
    . . . . .
    */
    BOAT,

    /*
    Still Life, 5x5 region, 4 live cells
    ------------------------------------
    . . . . .
    . . 0 . .
    . 0 . 0 .
    . . 0 . .
    . . . . .
    */
    TUB,

    /*
    Oscillator, 5x5 region, 3 live cells - 3 live cells
    ---------------------------------------------------
    . . . . .      . . . . .
    . . 0 . .      . . . . .
    . . 0 . .  __  . 0 0 0 .
    . . 0 . .      . . . . .
    . . . . .      . . . . .
    */
    BLINKER,

    /*
    Oscillator, 6x6 region, 6 live cells - 6 live cells
    ---------------------------------------------------
    . . . . . .      . . . . . .
    . . . . . .      . . . 0 . .
    . . 0 0 0 .  __  . 0 . . 0 .
    . 0 0 0 . .      . 0 . . 0 .
    . . . . . .      . . 0 . . .
    . . . . . .      . . . . . .
    */
    TOAD,

    /*
    Oscillator, 6x6 region, 6 live cells - 8 live cells
    ---------------------------------------------------
    . . . . . .      . . . . . .
    . 0 0 . . .      . 0 0 . . .
    . 0 . . . .  __  . 0 0 . . .
    . . . . 0 .      . . . 0 0 .
    . . . 0 0 .      . . . 0 0 .
    . . . . . .      . . . . . .
    */
    BEACON,

    /*
    Spaceship, 5x5 region, 5 live cells
    -----------------------------------
    . . . . .
    . . . 0 .
    . 0 . 0 .
    . . 0 0 .
    . . . . .
    */
    GLIDER,
    /*
    Creates a 3x3 grid of alive cells for debug purposes
    */
    DEBUG
};

class CellVector
{
public:
    CellVector(int width, int height);

    // Generates the starting conditions for the cell vector based on the chosen seed
    void generateSeed(Seed seed);
    void generateSeed(Seed seed, double isAliveChance);
    // Updates the boolean values of each cell based on the rules for Conway's Game of Life
    void tick();
    // Returns the height of the cell vector
    int getHeight();
    // Returns the width of the cell vector
    int getWidth();
    // Returns the cell vector
    std::vector<std::vector<bool>> getCellVector();

private:
    int height;
    int width;
    std::vector<std::vector<bool>> cellVector;

    // Returns a pseudo-random boolean to determine if a current cell is alive or dead when the seed is generated
    bool getRandomIsAliveBool(double isAliveChance); 
    // Returns an integer counting the amount of alive cells adjacent to the given coordinate
    int getAmountOfNeighbors(int x, int y);
};

#endif //!CELLVECTOR_H