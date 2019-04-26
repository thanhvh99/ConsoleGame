#ifndef PRINTER_H
#define PRINTER_H

#include "Minesweeper.h"

#define COL_WIDTH 3
#define ROW_HEIGHT 1

class Printer
{
private:
    Minesweeper* minesweeper;

public:
    //constructor
    Printer(Minesweeper &minesweeper);
    ~Printer();

    //function
    void printBoard(bool _2Line = false, bool printAll = false);
    void printValue(int x, int y);
    void printValue();

    void printFlagsSurround(bool _2Line = false);           //debug
    void printCoveredTilesSurround(bool _2Line = false);    //debug
    void printCovered(bool _2Line = false);                 //debug
    void printFlagged(bool _2Line = false);                 //debug
};

#endif // PRINTER_H
