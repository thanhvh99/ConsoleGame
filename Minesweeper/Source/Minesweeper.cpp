#include "Minesweeper.h"
#include "Console.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

//constructor
Minesweeper::Minesweeper()
{
    col = 0;
    row = 0;
    mine = 0;
    tiles = NULL;
}

Minesweeper::~Minesweeper()
{

}

//getter
int Minesweeper::getCol() {return col;}
int Minesweeper::getRow() {return row;}
int Minesweeper::getMine() {return mine;}
int Minesweeper::getValue(int x, int y) {return tiles[y][x].getValue();}
int Minesweeper::isCovered(int x, int y) {return tiles[y][x].isCovered();}
int Minesweeper::isFlagged(int x, int y) {return tiles[y][x].isFlagged();}
bool Minesweeper::isFinish()
{
    int count = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (tiles[i][j].isFlagged() || !tiles[i][j].isCovered())
                count++;
        }
    }
    return count == row * col;
}

//setter
void Minesweeper::toggleFlag(int x, int y)
{
    tiles[y][x].setFlagged(!tiles[y][x].isFlagged());
}

//function
void Minesweeper::createBoard(int cols, int rows, int mines)
{
    if (tiles != NULL)
    {
        for (int i = 0; i < row; i++)
        {
            delete tiles[i];
        }
        delete tiles;
    }

    col = cols;
    row = rows;
    mine = mines;

    tiles = new Tile*[row];
    for (int i = 0; i < row; i++)
    {
        tiles[i] = new Tile[col]();
    }
}

bool Minesweeper::selectCoveredTile(int x, int y)
{
    if (x < 0 || y < 0 || x >= col || y >= row) return true;
    if (tiles[y][x].isFlagged() || !tiles[y][x].isCovered()) return true;

    tiles[y][x].setCovered(false);
    if (tiles[y][x].getValue() == -1) return false;
    if (tiles[y][x].getValue() != 0) return true;

    bool notMine = true;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            notMine *= selectCoveredTile(x + i, y + j);
        }
    }
    return notMine;
}

bool Minesweeper::selectUncoveredTile(int x, int y)
{
    if (x < 0 || y < 0 || x >= col || y >= row) return true;
    if (tiles[y][x].isFlagged() || tiles[y][x].isCovered()) return true;

    int flags = getFlagsSurround(x, y);
    if (tiles[y][x].getValue() <= flags)
    {
        return uncoverTilesSurround(x, y);
    }
    return true;
}

void Minesweeper::setupBoard(int x, int y)
{
    int _y, _x;
    srand(time(NULL));
    int count = -1;
    do
    {
        count++;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                tiles[i][j].resetAll();
            }
        }
        for (int i = 0; i < mine; i++)
        {
            do
            {
                _x = rand() % col;
                _y = rand() % row;
            } while (tiles[_y][_x].isMine() || (x == _x && y == _y));
            tiles[_y][_x].setMine();
            increaseValueTilesSurround(_x, _y);
        }
    } while (!minesweeperSolver(x, y));

    gotoXY(0, row * 2 + 4);
    cout << "Failed generate: " << count;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            tiles[i][j].reset();
        }
    }
}

int Minesweeper::getCoveredTilesSurround(int x, int y)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        if (y + i < 0 || y + i >= row) continue;
        for (int j = -1; j <= 1; j++)
        {
            if (x + j < 0 || x + j >= col || (j == 0 && i == 0) || tiles[y + i][x + j].isFlagged()) continue;
            if (tiles[y + i][x + j].isCovered())
            {
                count++;
            }
        }
    }
    return count;
}

int Minesweeper::getFlagsSurround(int x, int y)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        if (y + i < 0 || y + i >= row) continue;
        for (int j = -1; j <= 1; j++)
        {
            if (x + j < 0 || x + j >= col || (j == 0 && i == 0)) continue;
            if (tiles[y + i][x + j].isFlagged())
            {
                count++;
            }
        }
    }
    return count;
}

void Minesweeper::increaseValueTilesSurround(int x, int y)
{
    for (int i = -1; i <= 1; i++)
    {
        if (y + i < 0 || y + i >= row) continue;
        for (int j = -1; j <= 1; j++)
        {
            if (x + j < 0 || x + j >= col) continue;
            tiles[y + i][x + j].increaseValue();
        }
    }
}

void Minesweeper::flagUncoveredTilesSurround(int x, int y)
{
    for (int i = -1; i <= 1; i++)
    {
        if (y + i < 0 || y + i >= row) continue;
        for (int j = -1; j <= 1; j++)
        {
            if (x + j < 0 || x + j >= col || (j == 0 && i == 0) || !tiles[y + i][x + j].isCovered()) continue;
            tiles[y + i][x + j].setFlagged(true);
        }
    }
}

void Minesweeper::resetBoard()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            tiles[i][j].resetAll();
        }
    }
}

bool Minesweeper::uncoverTilesSurround(int x, int y)
{
    bool rightFlag = true;
    for (int i = -1; i <= 1; i++)
    {
        if (y + i < 0 || y + i >= row) continue;
        for (int j = -1; j <= 1; j++)
        {
            if (x + j < 0 || x + j >= col || (j == 0 && i == 0)) continue;
            if (tiles[y][x].isFlagged() && !tiles[y][x].isMine())
                rightFlag = false;
            rightFlag *= selectCoveredTile(x + j, y + i);
        }
    }
    return rightFlag;
}

bool Minesweeper::minesweeperSolver(int x, int y)
{
    selectCoveredTile(x, y);
    bool action = true;
    bool** finish = new bool*[row];     // use to check if surround tiles are uncovered or flagged
    for (int i = 0; i < row; i++)
    {
        finish[i] = new bool[col]();
    }

    while (action)
    {
        action = false;
        for (y = 0; y < row; y++)
        {
            for (x = 0; x < col; x++)
            {
                // skip if 8 tiles surround are uncovered or tile is covered or tile is flagged
                if (finish[y][x] || tiles[y][x].isCovered() || tiles[y][x].isFlagged()) continue;

                // mark finish if 8 tiles surround are uncovered
                int coveredTiles = getCoveredTilesSurround(x, y);
                if (coveredTiles == 0)
                {
                    finish[y][x] = true;
                    continue;
                }

                // if number of flags around tile equals its value
                // then select all covered tiles around
                int flags = getFlagsSurround(x, y);
                if (flags == tiles[y][x].getValue())
                {
                    uncoverTilesSurround(x, y);
                    finish[y][x] = true;
                    action = true;
                }
                // if number of covered tiles left equals number of mine that is not flagged
                // then flag all covered tiles
                else if (flags + coveredTiles == tiles[y][x].getValue())
                {
                    flagUncoveredTilesSurround(x, y);
                    finish[y][x] = true;
                    action = true;
                }
            }
        }
        // if cant find any new flag with simple way, try with advance one
        if (!action && minesweeperAdvanceSolver(finish))
        {
           action = true;
        }
    }
    //count mines that are detected
    int count = 0;
    for (int i = 0; i < row; i++)
    {
        delete finish[i];   //free memory
        for (int j = 0; j < col; j++)
        {
            if (tiles[i][j].isFlagged())
            {
                count++;
            }
        }
    }
    delete finish;  //free memory
    //  board is solvable if number of detected mines = total mines
    return count == mine;
}

bool Minesweeper::minesweeperAdvanceSolver(bool** finish)
{
    bool action = false;
    for (int y = 0; y < row; y++)
    {
        for (int x = 0; x < col; x++)
        {
            if (finish[y][x] || tiles[y][x].isCovered()) continue;
            int undetectMines = tiles[y][x].getValue() - getFlagsSurround(x, y);
            if (undetectMines <= 1) continue;
            //get position of covered tiles surround
            vector<int> vectorX;
            vector<int> vectorY;
            for (int i = -1; i <= 1; i++)
            {
                if (y + i < 0 || y + i >= row) continue;
                for (int j = -1; j <= 1; j++)
                {
                    if (x + j < 0 || x + j >= col) continue;
                    if (tiles[y + i][x + j].isCovered() && !tiles[y + i][x + j].isFlagged())
                    {
                        vectorX.push_back(x + j);
                        vectorY.push_back(y + i);
                    }
                }
            }
            int* frequency = new int[vectorX.size()]();
            int count = 0;
            countPossibleWays(vectorX, vectorY, undetectMines, frequency, count);
            for (int i = vectorX.size() - 1; i >= 0; i--)
            {
                if (isFlagged(vectorX[i], vectorY[i]))
                {
                    toggleFlag(vectorX[i], vectorY[i]);
                }
            }
            for (int i = vectorX.size() - 1; i >= 0; i--)
            {
                if (frequency[i] == count)
                {
                    action = true;
                    toggleFlag(vectorX[i], vectorY[i]);
                }
            }
        }
    }
    return action;
}

void Minesweeper::countPossibleWays(vector<int> &vectorX, vector<int> &vectorY, int undetectMines, int* &frequency, int &count, int start)
{
    if (undetectMines == 0)
    {
        bool accept = true;
        for (int i = vectorX.size() - 1; i >= 0; i--)
        {
            if (!tiles[vectorY[i]][vectorX[i]].isFlagged()) continue;
            for (int a = -1; a <= 1; a++)
            {
                if (vectorY[i] + a < 0 || vectorY[i] + a >= row) continue;
                for (int b = -1; b <= 1; b++)
                {
                    if (vectorX[i] + b < 0 || vectorX[i] + b >= col ||
                        tiles[vectorY[i] + a][vectorX[i] + b].isFlagged() ||
                        tiles[vectorY[i] + a][vectorX[i] + b].isCovered())
                        continue;
                    if (getFlagsSurround(vectorX[i] + b, vectorY[i] + a) > getValue(vectorX[i] + b, vectorY[i] + a))
                    {
                        //exit all loop
                        accept = false;
                        i = -1;
                        a = 2;
                        b = 2;
                    }
                }
            }
        }
        if (accept)
        {
            for (int i = vectorX.size() - 1; i >= 0; i--)
            {
                if (isFlagged(vectorX[i], vectorY[i]))
                {
                    frequency[i]++;
                }
            }
            count++;
        }
        return;
    }
    int end = vectorX.size() - undetectMines;
    for (int index = start; index <= end; index++)
    {
        toggleFlag(vectorX[index], vectorY[index]);
        countPossibleWays(vectorX, vectorY, undetectMines - 1, frequency, count, index + 1);
        toggleFlag(vectorX[index], vectorY[index]);
    }
}







