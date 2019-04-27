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
    /*
     *  constructor
     */
    Minesweeper();
    ~Minesweeper();


    /*
     *  getter
     */
    int getCol();
    int getRow();
    int getMine();
    int getValue(int x, int y);
    bool isCovered(int x, int y);
    bool isFlagged(int x, int y);
    bool isFinish(); //  return true if the board is completed otherwise return false;


    /*
     *  setter
     */
    void toggleFlag(int x, int y);


    /*
     *  function
     */
    //  save new values of board and initialize tiles
    void createBoard(const int* difficulty);

    //  create a solvable board
    void setupBoard(int x, int y);

    //  select covered tile at position (x, y); return true if no mine is uncovered otherwise return false
    bool selectCoveredTile(int x, int y);

    //  select all covered tiles around tile at posion (x, y); return true if no mine is uncovered otherwise return false
    bool selectUncoveredTile(int x, int y);

private:
    /*
     *  function
     */
    //  keep mines position, set flagged and covered of all tiles to default
    void resetBoard();

    //  turn board to default
    void resetAll();

    //  use to solve board; return true if successfully solved otherwise return false;
    bool solve(int x, int y);

    //  detect mines that are hard to find; return true if find at least one otherwise return false; no guessing - only logic
    bool minesFinder(bool** finish);

    //  increase value of 8 tiles surround tile at position (x, y)
    void increaseValueTilesSurround(int x, int y);

    //  return the number of covered tiles surround tile at position (x, y)
    int getCoveredTilesSurround(int x, int y);

    //  return the number of flags surround tile at position (x, y)
    int getFlagsSurround(int x, int y);

    //  flag all covered tiles surround tile at position (x, y)
    void flagCoveredTilesSurround(int x, int y);

    //  uncover all covered tiles surround tile at position (x, y); return true if no mine is uncovered otherwise return false
    bool uncoverTilesSurround(int x, int y);

    //  find all possible ways to put number of undetected mines into all tiles with position in 2 vectors
    void countPossibleWays(vector<int> &vectorX, vector<int> &vectorY, int undetectedMines, int* &frequency, int &count, int start = 0);

};

#endif // MINESWEEPER_H
