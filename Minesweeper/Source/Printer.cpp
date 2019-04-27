#include "Printer.h"
#include "Console.h"
#include <iostream>

using namespace std;

//constructor
Printer::Printer(Minesweeper &minesweeper)
{
    this->minesweeper = &minesweeper;
    _2Line = true;
    tableColor = 7;
    numberColor = 7;
    flagColor = 14;
    mineColor = 4;
}

Printer::~Printer()
{

}

//getter
bool Printer::is2Line() {return _2Line;}
int Printer::getTableCoror() {return tableColor;}
int Printer::getNumberColor() {return numberColor;}
int Printer::getFlagColor() {return flagColor;}
int Printer::getMineColor() {return mineColor;}

//setter
void Printer::set2Line(bool _2Line) {this->_2Line = _2Line;}
void Printer::setTableColor(int color) {tableColor = color;}
void Printer::setNumberColor(int color) {numberColor = color;}
void Printer::setFlagColor(int color) {flagColor = color;}
void Printer::setMineColor(int color) {mineColor = color;}

//function
void Printer::printBoard(bool printAll)
{
    changeColor(tableColor);
    table(0, 2, minesweeper->getCol(), minesweeper->getRow(), COL_WIDTH, ROW_HEIGHT, _2Line);
    changeColor(numberColor);
    int row = minesweeper->getRow();
    int col = minesweeper->getCol();
    if (printAll)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                gotoXY(2 + j * (COL_WIDTH + 1), 3 + i * (ROW_HEIGHT + 1));
                if (minesweeper->getValue(j, i) == -1)
                {
                    changeColor(mineColor);
                    cout << "*";
                }
                else
                {
                    changeColor(numberColor);
                    cout << minesweeper->getValue(j, i);
                }
            }
        }
    }
    else
    {
        for (int y = 0; y < row; y++)
        {
            for (int x = 0; x < col; x++)
            {
                if (minesweeper->isFlagged(x, y))
                {
                    gotoXY(2 + x * (COL_WIDTH + 1), 3 + y * (ROW_HEIGHT + 1));
                    changeColor(flagColor);
                    cout << "F";
                }
                else if (!minesweeper->isCovered(x, y))
                {
                    gotoXY(2 + x * (COL_WIDTH + 1), 3 + y * (ROW_HEIGHT + 1));
                    changeColor(numberColor);
                    cout << minesweeper->getValue(x, y);
                }
            }
        }
    }
    changeColor(7);
}

void Printer::printValue(int x, int y)
{
    gotoXY(2 + x * (COL_WIDTH + 1), 3 + y * (ROW_HEIGHT + 1));
    if (minesweeper->isFlagged(x, y))
    {
        changeColor(flagColor);
        cout << "F";
    }
    else if (!minesweeper->isCovered(x, y))
    {
        int n = minesweeper->getValue(x, y);
        if (n == -1)
        {
            changeColor(mineColor);
            cout << '*';
        }
        else
        {
            changeColor(numberColor);
            cout << n;
        }
    }
    else
    {
        cout << " ";
    }
    changeColor(7);
}

void Printer::printValue()
{
    int row = minesweeper->getRow();
    int col = minesweeper->getCol();
    for (int y = 0; y < row; y++)
    {
        for (int x = 0; x < col; x++)
        {
            if (minesweeper->isFlagged(x, y))
            {
                gotoXY(2 + x * (COL_WIDTH + 1), 3 + y * (ROW_HEIGHT + 1));
                changeColor(flagColor);
                cout << "F";
            }
            else if (!minesweeper->isCovered(x, y))
            {
                gotoXY(2 + x * (COL_WIDTH + 1), 3 + y * (ROW_HEIGHT + 1));
                int n = minesweeper->getValue(x, y);
                if (n == -1)
                {
                    changeColor(mineColor);
                    cout << '*';
                }
                else
                {
                    changeColor(numberColor);
                    cout << n;
                }
            }
        }
    }
    changeColor(7);
}
