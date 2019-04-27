#include "Console.h"
#include "Minesweeper.h"
#include "Printer.h"
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <time.h>

#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ENTER 13
#define SPACE 32
#define ESCAPE 27
#define BACKSPACE 8


using namespace std;

//
//  global variable
//
const int difficultyData[][3] = {{8, 8, 10}, {16, 16, 40}, {30, 16, 99}};
int difficulty = 0;

Minesweeper minesweeper;
Printer printer(minesweeper);


//
//  declare function
//
void playState();
void difficultyState();
void optionState();
void controlState();
void exitState();
void menuState(int &state);


//
//  main function
//
int main()
{
    char* name = new char[11]{'M', 'i', 'n', 'e', 's', 'w', 'e', 'e', 'p', 'e', 'r'};
    setWindowFullscreen(name);

    int state = 5;
    bool running = true;
    while (running)
    {

        switch (state)
        {
            case 0:
                playState();
                state = 5;
                break;
            case 1:
                difficultyState();
                state = 5;
                break;
            case 2:
                optionState();
                state = 5;
                break;
            case 3:
                controlState();
                state = 5;
                break;
            case 4:
                exitState();
                running = false;
                break;
            case 5:
                menuState(state);
                break;
        }
    }
}

//
//  implement function
//
void playState()
{
    system("cls");

    minesweeper.createBoard(difficultyData[difficulty]);

    int x = 0;
    int y = 0;
    int col = difficultyData[difficulty][0];
    int row = difficultyData[difficulty][1];
    int mine = difficultyData[difficulty][2];
    bool firstPick = true;
    int status = 0;
    time_t now = time(NULL);
    long _time = 0;
    cout << "Mine: " << mine << endl;
    cout << "Time: ";
    cout << _time / 60 << ":" << _time % 60;
    printer.printBoard();
    gotoXY(2, 3);

    while (status == 0)
    {
        if (kbhit())
        {
            char key = getch();
            switch (key)
            {
                case 'w':
                case 'W':
                case UP_ARROW: y = (y - 1 + row) % row; break;
                case 's':
                case 'S':
                case DOWN_ARROW: y = (y + 1) % row; break;
                case 'A':
                case 'a':
                case LEFT_ARROW: x = (x - 1 + col) % col; break;
                case 'D':
                case 'd':
                case RIGHT_ARROW: x = (x + 1) % col; break;
                case ENTER:
                case SPACE:
                    if (firstPick)
                    {
                        now = time(NULL);
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
                    if (mine == 0 && minesweeper.isFinish())
                    {
                        status = 1;
                    }
                    printer.printValue();
                    break;
                //  F = flag
                case 'F':
                case 'f':
                    if (firstPick) break;
                    if (minesweeper.isCovered(x, y))
                    {
                        minesweeper.toggleFlag(x, y);
                        if (minesweeper.isFlagged(x, y))
                        {
                            mine--;
                        }
                        else
                        {
                            mine++;
                        }
                    }
                    gotoXY(6, 0);
                    cout << mine << "   ";
                    printer.printValue(x, y);
                    if (mine == 0 && minesweeper.isFinish())
                    {
                        status = 1;
                    }
                    break;
                case ESCAPE:
                case BACKSPACE:
                    return;
            }
            gotoXY(2 + x * 4, 3 + y * 2);
        }
        if (!firstPick && time(NULL) > now + _time)
        {
            _time = time(NULL) - now;
            gotoXY(6, 1);
            cout << _time / 60 << ":" << _time % 60 << "   ";
            gotoXY(2 + x * 4, 3 + y * 2);
        }
        //  loop delay
        Sleep(10);
    }

    printer.printBoard(true);
    gotoXY(0, row * 2 + 5);
    if (status == 1)
    {
        cout << "You win.\n";
    }
    else
    {
        cout << "You lose.\n";
    }
    Sleep(3000);
    system("pause");
}

void difficultyState()
{
    system("cls");
    cout << "Minesweeper - Made by thanhvh99\n";
    cout << "-------------------------------\n\n";
    cout << "   Beginner\n";
    cout << "   Intermediate\n";
    cout << "   Expert\n\n";
    cout << "-------------------------------\n";
    cout << "Find more console games at \"https://github.com/thanhvh99/ConsoleGame\".";

    bool running = true;
    gotoXY(1, difficulty + 3);
    cout << ">";
    while (running)
    {
        if (kbhit())
        {
            char key = getch();
            gotoXY(1, difficulty + 3);
            cout << " ";
            switch (key)
            {
                case UP_ARROW:
                case LEFT_ARROW:
                case 'w':
                case 'W':
                case 'a':
                case 'A':
                    difficulty = (difficulty + 2) % 3;
                    break;
                case DOWN_ARROW:
                case RIGHT_ARROW:
                case 's':
                case 'S':
                case 'd':
                case 'D':
                    difficulty = (difficulty + 1) % 3;
                    break;
                case ENTER:
                case SPACE:
                case ESCAPE:
                case BACKSPACE:
                    running = false;
                    break;
            }
            gotoXY(1, difficulty + 3);
            cout << ">";
        }
        //  loop delay
        Sleep(10);
    }
}

void optionState()
{
    system("cls");
    cout << "Minesweeper - Made by thanhvh99\n";
    cout << "-------------------------------\n";
    cout << "   Table line:     ";
    if (printer.is2Line())
        cout << "2\n";
    else
        cout << "1\n";
    cout << "   Table color:    ";
    changeColor(printer.getTableCoror());
    cout << printer.getTableCoror() << "   \n";
    changeColor(7);
    cout << "   Number color:   ";
    changeColor(printer.getNumberColor());
    cout << printer.getNumberColor() << "   \n";
    changeColor(7);
    cout << "   Flag color:     ";
    changeColor(printer.getFlagColor());
    cout << printer.getFlagColor() << "   \n";
    changeColor(7);
    cout << "   Mine color:     ";
    changeColor(printer.getMineColor());
    cout << printer.getMineColor() << "   \n";
    changeColor(7);
    cout << "-------------------------------\n";
    cout << "Find more console games at \"https://github.com/thanhvh99/ConsoleGame\".";

    int option = 0;
    int maxOptions = 5;
    bool running = true;
    gotoXY(1, 2);
    cout << ">";
    while (running)
    {
        if (kbhit())
        {
            char key = getch();
            gotoXY(1, option + 2);
            cout << " ";
            switch (key)
            {
                case UP_ARROW:
                case 'w':
                case 'W':
                    option = (option - 1 + maxOptions) % maxOptions;
                    break;
                case DOWN_ARROW:
                case 's':
                case 'S':
                    option = (option + 1) % maxOptions;
                    break;
                case LEFT_ARROW:
                case 'a':
                case 'A':
                    switch (option)
                    {
                        case 0:
                            printer.set2Line(!printer.is2Line());
                            break;
                        case 1:
                            printer.setTableColor((printer.getTableCoror() + 14) % 15);
                            break;
                        case 2:
                            printer.setNumberColor((printer.getNumberColor() + 14) % 15);
                            break;
                        case 3:
                            printer.setFlagColor((printer.getFlagColor() + 14) % 15);
                            break;
                        case 4:
                            printer.setMineColor((printer.getMineColor() + 14) % 15);
                            break;
                    }
                    break;
                case RIGHT_ARROW:
                case 'd':
                case 'D':
                case ENTER:
                case SPACE:
                    switch (option)
                    {
                        case 0:
                            printer.set2Line(!printer.is2Line());
                            break;
                        case 1:
                            printer.setTableColor((printer.getTableCoror() + 1) % 15);
                            break;
                        case 2:
                            printer.setNumberColor((printer.getNumberColor() + 1) % 15);
                            break;
                        case 3:
                            printer.setFlagColor((printer.getFlagColor() + 1) % 15);
                            break;
                        case 4:
                            printer.setMineColor((printer.getMineColor() + 1) % 15);
                            break;
                    }
                    break;
                case ESCAPE:
                case BACKSPACE:
                    running = false;
                    break;
            }
            gotoXY(19, option + 2);
            switch (option)
            {
                case 0:
                    if (printer.is2Line())
                        cout << "2\n";
                    else
                        cout << "1\n";
                    break;
                case 1:
                    changeColor(printer.getTableCoror());
                    cout << printer.getTableCoror() << "   ";
                    changeColor(7);
                    break;
                case 2:
                    changeColor(printer.getNumberColor());
                    cout << printer.getNumberColor() << "   ";
                    changeColor(7);
                    break;
                case 3:
                    changeColor(printer.getFlagColor());
                    cout << printer.getFlagColor() << "   ";
                    changeColor(7);
                    break;
                case 4:
                    changeColor(printer.getMineColor());
                    cout << printer.getMineColor() << "   ";
                    changeColor(7);
                    break;
            }
            gotoXY(1, option + 2);
            cout << ">";
        }
        //  loop delay
        Sleep(10);
    }
}

void controlState()
{
    system("cls");
    cout << "Minesweeper - Made by thanhvh99\n";
    cout << "-------------------------------\n";
    cout << "   Enter/Space     -   Select\n";
    cout << "   W,A,S,D/Arrows  -   Move\n";
    cout << "   F               -   Flag\n";
    cout << "   Esc/Backspace   -   Back\n\n";
    cout << "-------------------------------\n";
    cout << "Find more console games at \"https://github.com/thanhvh99/ConsoleGame\".";
    while (!kbhit())
    {
        Sleep(10);
    }
}

void exitState()
{
    system("cls");
    cout << "Minesweeper - Made by thanhvh99\n";
    cout << "-------------------------------\n\n\n";
    cout << "Thank you for playing my game.\n\n\n";
    cout << "-------------------------------\n";
    cout << "Find more console games at \"https://github.com/thanhvh99/ConsoleGame\".";
}

void menuState(int &state)
{
    system("cls");
    cout << "Minesweeper - Made by thanhvh99\n";
    cout << "-------------------------------\n";
    cout << "   Play\n";
    cout << "   Difficulty - ";
    switch (difficulty)
    {
        case 0: cout << "Beginner\n"; break;
        case 1: cout << "Intermediate\n"; break;
        case 2: cout << "Expert\n"; break;
    }
    cout << "   Option\n";
    cout << "   Control\n";
    cout << "   Exit\n";
    cout << "-------------------------------\n";
    cout << "Find more console games at \"https://github.com/thanhvh99/ConsoleGame\".";

    bool running = true;
    int option = 0;
    int maxOptions = 5;
    gotoXY(1, 2);
    cout << ">";
    while (running)
    {
        if (kbhit())
        {
            char key = getch();
            gotoXY(1, option + 2);
            cout << " ";
            switch (key)
            {
                case UP_ARROW:
                case LEFT_ARROW:
                case 'w':
                case 'W':
                case 'a':
                case 'A':
                    option = (option - 1 + maxOptions) % maxOptions;
                    break;
                case DOWN_ARROW:
                case RIGHT_ARROW:
                case 's':
                case 'S':
                case 'd':
                case 'D':
                    option = (option + 1) % maxOptions;
                    break;
                case ENTER:
                case SPACE:
                    state = option;
                    running = false;
                    break;
            }
            gotoXY(1, option + 2);
            cout << ">";
        }
        //  loop delay
        Sleep(10);
    }
}
