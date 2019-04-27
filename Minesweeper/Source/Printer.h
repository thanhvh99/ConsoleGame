#ifndef PRINTER_H
#define PRINTER_H

#include "Minesweeper.h"

#define COL_WIDTH 3
#define ROW_HEIGHT 1

class Printer
{
private:
    Minesweeper* minesweeper;
    bool _2Line;
    int tableColor;
    int numberColor;
    int flagColor;
    int mineColor;

public:
    //constructor
    Printer(Minesweeper &minesweeper);
    ~Printer();

    //getter
    bool is2Line();
    int getTableCoror();
    int getNumberColor();
    int getFlagColor();
    int getMineColor();

    //setter
    void set2Line(bool _2Line);
    void setTableColor(int color);
    void setNumberColor(int color);
    void setFlagColor(int color);
    void setMineColor(int color);

    //function
    void printBoard(bool printAll = false);
    void printValue(int x, int y);
    void printValue();
};

#endif // PRINTER_H
