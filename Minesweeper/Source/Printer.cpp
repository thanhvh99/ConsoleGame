#include "Printer.h"
#include "Console.h"
#include <iostream>

using namespace std;

//constructor
Printer::Printer(Minesweeper &minesweeper)
{
    this->minesweeper = &minesweeper;
}

Printer::~Printer()
{

}

//function
void Printer::printBoard(bool _2Line, bool printAll)
{
    table(0, 2, minesweeper->getCol(), minesweeper->getRow(), COL_WIDTH, ROW_HEIGHT, _2Line);
    int row = minesweeper->getRow();
    int col = minesweeper->getCol();
    if (printAll)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                gotoXY(2 + j * (COL_WIDTH + 1), 3 + i * (ROW_HEIGHT + 1));
                cout << minesweeper->getValue(j, i);
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
                    cout << "P";
                }
                else if (!minesweeper->isCovered(x, y))
                {
                    gotoXY(2 + x * (COL_WIDTH + 1), 3 + y * (ROW_HEIGHT + 1));
                    cout << minesweeper->getValue(x, y);
                }
            }
        }
    }
}

void Printer::printValue(int x, int y)
{
    gotoXY(2 + x * (COL_WIDTH + 1), 3 + y * (ROW_HEIGHT + 1));
    if (minesweeper->isFlagged(x, y))
    {
        changeColor(4);
        cout << "P";
        changeColor(7);
    }
    else if (!minesweeper->isCovered(x, y))
    {
        int n = minesweeper->getValue(x, y);
        if (n == -1)
        {
            cout << '*';
        }
        else
        {
            cout << n;
        }
    }
    else
    {
        cout << " ";
    }
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
                changeColor(4);
                cout << "P";
                changeColor(7);
            }
            else if (!minesweeper->isCovered(x, y))
            {
                gotoXY(2 + x * (COL_WIDTH + 1), 3 + y * (ROW_HEIGHT + 1));
                int n = minesweeper->getValue(x, y);
                if (n == -1)
                {
                    cout << '*';
                }
                else
                {
                    cout << n;
                }
            }
        }
    }
}
