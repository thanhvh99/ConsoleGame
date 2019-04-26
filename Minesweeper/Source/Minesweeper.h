#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include "Tile.h"

using namespace std;

/*
//  Board
//  0 - 8 ~ number
//  -1 ~ mine
//
//  Status
//  0 ~ covered
//  1 ~ uncovered
//  2 ~ right flag
//  3 ~ wrong flag
*/


class Minesweeper
{
private:
    int col;
    int row;
    int mine;
    Tile** tiles;

public:
    //constructor
    Minesweeper();
    ~Minesweeper();

    //getter
    int getCol();
    int getRow();
    int getMine();
    int getValue(int x, int y);
    int isCovered(int x, int y);
    int isFlagged(int x, int y);
    bool isFinish();

    //setter
    void toggleFlag(int x, int y);

    //function
    void createBoard(int cols, int rows, int mines);
    bool selectCoveredTile(int x, int y);
    bool selectUncoveredTile(int x, int y);
    void setupBoard(int x, int y);
    bool minesweeperSolver(int x, int y);
    bool minesweeperAdvanceSolver(bool** finish);
    void resetBoard();

    void increaseValueTilesSurround(int x, int y);
    int getCoveredTilesSurround(int x, int y);
    int getFlagsSurround(int x, int y);
    void flagUncoveredTilesSurround(int x, int y);
    bool uncoverTilesSurround(int x, int y);

private:
    //function
    void countPossibleWays(vector<int> &vectorX, vector<int> &vectorY, int undetectMines, int* &frequency, int &count, int start = 0);

};

#endif // MINESWEEPER_H
