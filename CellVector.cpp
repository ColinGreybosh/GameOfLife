#include <cstdlib>
#include <ctime>
#include <vector>

#include "CellVector.h"

CellVector::CellVector(int width, int height)
{
    this->width = width;
    this->height = height;
    cellVector.resize(getVectorWidth(), std::vector<bool>(getVectorHeight(), 0));
}

void CellVector::generateSeed(Seed seed)
{
    // This switch generates either a random seed or a predefined still-life, oscillator, or space-ship pattern
    switch (seed)
    {
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
        generateSeed(DEBUG);
        break;
    } 
}

void CellVector::generateSeed(double isAliveChance)
{
    srand(static_cast <unsigned> (time(0)));

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            cellVector[x][y] = getRandomIsAliveBool(isAliveChance);
        }
    }
}
    

void CellVector::tick()
{
    std::vector<std::vector<bool>> vectorCopy = cellVector;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int amountOfNeighbors = getAmountOfNeighbors(x, y);
            // Alive and has 2 neighbors - Cell Lives | Has 3 neighbors - Cell Lives/Is Born | Neither previous conditions satisfied - Cell Dies
            vectorCopy[x][y] = cellVector[x][y] && amountOfNeighbors == 2 || amountOfNeighbors == 3;
        }
    }

    cellVector.swap(vectorCopy);
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

    // Deduct 1 from neighborCount if the cell looking for neighbors is alive
    if (cellVector[x][y])
    {
        neighborCount--;
    }

    return neighborCount;
}

int CellVector::getVectorWidth()
{
    return width;
}

int CellVector::getVectorHeight()
{
    return height;
}

std::vector<std::vector<bool>> CellVector::getCellVector()
{
    return cellVector;
}

bool CellVector::getRandomIsAliveBool(double isAliveChance)
{
    double chance = static_cast <float> (rand() / static_cast <float> (RAND_MAX));

    return (isAliveChance >= chance);
}