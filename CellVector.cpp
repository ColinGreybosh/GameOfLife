#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "CellVector.h"

CellVector::CellVector(int height, int width, double isAliveChance)
{
    this->height = height;
    this->width = width;
    this->isAliveChance = isAliveChance;
    cellVector.resize(getWidth(), std::vector<bool>(getHeight(), 0));
}

void CellVector::generateSeed(Seed seed)
{
    // This switch generates either a random seed or a predefined still-life, oscillator, or space-ship pattern
    switch (seed)
    {
    case RANDOM:
        srand(static_cast <unsigned> (time(0)));

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                cellVector[x][y] = getRandomIsAliveBool();
            }
        }
        break;

    case BLOCK:
        cellVector[1][1] = 1;
        cellVector[1][2] = 1;
        cellVector[2][1] = 1;
        cellVector[2][2] = 1;
        break;

    case BEEHIVE:
        cellVector[1][2] = 1;
        cellVector[2][1] = 1;
        cellVector[2][3] = 1;
        cellVector[3][1] = 1;
        cellVector[3][3] = 1;
        cellVector[4][2] = 1;
        break;

    case LOAF:
        cellVector[1][2] = 1;
        cellVector[2][1] = 1;
        cellVector[2][3] = 1;
        cellVector[3][1] = 1;
        cellVector[3][4] = 1;
        cellVector[4][2] = 1;
        cellVector[4][3] = 1;
        break;

    case BOAT:
        cellVector[1][1] = 1;
        cellVector[1][2] = 1;
        cellVector[2][1] = 1;
        cellVector[2][3] = 1;
        cellVector[3][2] = 1;
        break;

    case TUB:
        cellVector[1][2] = 1;
        cellVector[2][1] = 1;
        cellVector[2][3] = 1;
        cellVector[3][2] = 1;
        break;

    case BLINKER:
        cellVector[2][1] = 1;
        cellVector[2][2] = 1;
        cellVector[2][3] = 1;
        break;

    case TOAD:
        cellVector[1][3] = 1;
        cellVector[2][2] = 1;
        cellVector[2][3] = 1;
        cellVector[3][2] = 1;
        cellVector[3][3] = 1;
        cellVector[4][2] = 1;
        break;

    case BEACON:
        cellVector[1][1] = 1;
        cellVector[1][2] = 1;
        cellVector[2][1] = 1;
        cellVector[3][4] = 1;
        cellVector[4][3] = 1;
        cellVector[4][4] = 1;
        break;

    case GLIDER:
        cellVector[1][2] = 1;
        cellVector[2][3] = 1;
        cellVector[3][1] = 1;
        cellVector[3][2] = 1;
        cellVector[3][3] = 1;
        break;

    case DEBUG:
        for (int x = 1; x <= 3; x++)
        {
            for (int y = 1; y <= 3; y++)
            {
                cellVector[x][y] = 1;
            }
        }
        break;

    default:
        generateSeed(RANDOM);
        break;
    } 
}

void CellVector::tick()
{
    std::vector<std::vector<bool>> vectorCopy = cellVector;

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int amountOfNeighbors = getAmountOfNeighbors(x, y);
            // Alive and has 2 neighbors - Cell Lives
            if (cellVector[x][y] && amountOfNeighbors == 2)
            {
                vectorCopy[x][y] = 1;
            }
            // Has 3 neighbors - Cell Lives/Is Born
            else if (amountOfNeighbors == 3)
            {
                vectorCopy[x][y] = 1;
            }
            // Neither previous conditions satisfied - Cell Dies
            else
            {
                vectorCopy[x][y] = 0;
            }
        }
    }

    cellVector.swap(vectorCopy);
}

void CellVector::printVector()
{
    std::string output = "";

    for (int x = 0; x < (width - 1); x++)
    {
        for (int y = 0; y < (height - 1); y++)
        {
            // Prints "0" if alive, "." if dead
            (cellVector[x][y]) ? output.append("0") : output.append(".");
            output.append(" ");
        }
        output.append("\n");
    }

    for (int i = 0; i < 10; i++)
    {
        output.append("\n");
    }

    output.append("\n");
    std::cout << output;
}

int CellVector::getHeight()
{
    return height;
}

int CellVector::getWidth()
{
    return width;
}

std::vector<std::vector<bool>> CellVector::getCellVector()
{
    return cellVector;
}

bool CellVector::getRandomIsAliveBool()
{
    double chance = static_cast <float> (rand() / static_cast <float> (RAND_MAX));

    return (isAliveChance >= chance);
}

int CellVector::getAmountOfNeighbors(int x, int y)
{
    int neighborCount = 0;

    for (int i = -1; i <= 1; i++)
    {
        int currentCol = x + i;
        for (int j = -1; j <= 1; j++)
        {
            int currentRow = y + j;
            bool outOfBounds = ((currentCol < 0) || (currentCol >= width) || (currentRow < 0) || (currentRow >= height));

            if (!outOfBounds && cellVector[currentCol][currentRow])
            {
                neighborCount++;
            }
        }
    }

    // Deduct 
    if (cellVector[x][y])
    {
        neighborCount--;
    }

    return neighborCount;
}