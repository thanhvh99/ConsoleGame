#include "Console.h"
#include "Minesweeper.h"
#include "Printer.h"
#include <windows.h>
#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
    int col = 30;
    int row = 16;
    int mine = 99;
    char* name = new char[11]{'M', 'i', 'n', 'e', 's', 'w', 'e', 'e', 'p', 'e', 'r'};
    setWindowFullscreen(name);
    Minesweeper minesweeper;
    Printer printer(minesweeper);
    minesweeper.createBoard(col, row, mine);
    printer.printBoard(true);

    //game loop
    bool running = true;
    while (running)
    {
        system("cls");
        int x = 0;
        int y = 0;
        int minesLeft = mine;
        cout << "Mines: " << minesLeft << "   ";
        minesweeper.resetBoard();
        printer.printBoard(true);
        gotoXY(2, 3);
        bool firstPick = true;
        int status = 0;
        while (status == 0)
        {
            if (kbhit())
            {
                char key = getch();
                switch (key)
                {
                    case 72: y = (y - 1 + row) % row; break;
                    case 80: y = (y + 1) % row; break;
                    case 75: x = (x - 1 + col) % col; break;
                    case 77: x = (x + 1) % col; break;
                    case 13:
                        if (firstPick)
                        {
                            minesweeper.setupBoard(x, y);
                            firstPick = false;
                        }
                        if (minesweeper.isCovered(x, y))
                        {
                            if (!minesweeper.selectCoveredTile(x, y))
                            {
                                status = -1;
                            }
                        }
                        else if (!minesweeper.selectUncoveredTile(x, y))
                        {
                            status = -1;
                        }
                        if (minesLeft == 0 && minesweeper.isFinish())
                        {
                            status = 1;
                        }
                        printer.printValue();
                        break;
                    case 32:
                        if (firstPick) break;
                        if (minesweeper.isCovered(x, y))
                        {
                            minesweeper.toggleFlag(x, y);
                            if (minesweeper.isFlagged(x, y))
                            {
                                minesLeft--;
                            }
                            else
                            {
                                minesLeft++;
                            }
                        }
                        gotoXY(7, 0);
                        cout << minesLeft << "   ";
                        printer.printValue(x, y);
                        if (minesLeft == 0 && minesweeper.isFinish())
                        {
                            status = 1;
                        }
                        break;
                }
                gotoXY(2 + x * 4, 3 + y * 2);
            }
            //loop delay
            Sleep(10);
        }
        gotoXY(0, row * 2 + 5);
        if (status == 1)
        {
            cout << "You win. ";
        }
        else
        {
            cout << "You lose. ";
        }
        cout << "New game? (y/n) ";
        char key;
        cin >> key;
        running = key == 'y';
    }
}
