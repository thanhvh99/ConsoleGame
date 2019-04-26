#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <iostream>
#include "Console.h"


using namespace std;

void gotoXY(int x, int y)
{
    COORD coor;
    coor.X = x;
    coor.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
}

void clearScreen()
{
    system("cls");
}

void setWindowFullscreen(char name[])
{
    SetConsoleTitle(name);
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}

void setWindow(int width, int height, char name[])
{
    COORD coord;
    coord.X = width;
    coord.Y = height;

    SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = height - 1;
    Rect.Right = width - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(Handle, coord);
    SetConsoleWindowInfo(Handle, TRUE, &Rect);
    SetConsoleTitle(name);
}

void changeColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void rectangleBorder(int x, int y, int height, int width, bool _2Line)
{
    upLeftCorner(x, y, _2Line);
    downLeftCorner(x, y + height - 1, _2Line);
    downRightCorner(x + width - 1, y + height - 1, _2Line);
    upRightCorner(x + width - 1, y, _2Line);

    horizontalLine(x + 1, y, width - 2, _2Line);
    horizontalLine(x + 1, y + height - 1, width-2, _2Line);
    verticalLine(x, y + 1, height - 2, _2Line);
    verticalLine(x + width - 1, y + 1, height - 2, _2Line);
}

void horizontalLine(int x, int y, int length, bool _2Line)
{
    gotoXY(x, y);
    if (!_2Line)
    {
        for (int i = 0; i < length; i++)
            cout << (char)196;
    }
    else
    {
        for (int i = 0; i < length; i++)
            cout << (char)205;
    }
}

void verticalLine(int x, int y, int length, bool _2Line)
{
    if (!_2Line)
    {
        for (int i = 0; i < length; i++)
        {
            gotoXY(x, y + i);
            cout << (char)179;
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            gotoXY(x, y + i);
            cout << (char)186;
        }
    }
}

void tShapeUp(int x, int y, bool _2Line)
{
    gotoXY(x, y);
    if (!_2Line) cout << (char)193;
    else cout << (char)202;
}

void tShapeDown(int x, int y, bool _2Line)
{
    gotoXY(x, y);
    if (!_2Line) cout << (char)194;
    else cout << (char)203;
}

void tShapeLeft(int x, int y, bool _2Line)
{
    gotoXY(x, y);
    if (!_2Line) cout << (char)180;
    else cout << (char)185;
}

void tShapeRight(int x, int y, bool _2Line)
{
    gotoXY(x, y);
    if (!_2Line) cout << (char)195;
    else cout << (char)204;
}

void crossShape(int x, int y, bool _2Line)
{
    gotoXY(x, y);
    if (!_2Line) cout << (char)197;
    else cout << (char)206;
}

void upLeftCorner(int x, int y, bool _2Line)
{
    gotoXY(x, y);
    if (!_2Line) cout << (char)218;
    else cout << (char)201;
}

void upRightCorner(int x, int y, bool _2Line)
{
    gotoXY(x, y);
    if (!_2Line) cout << (char)191;
    else cout << (char)187;
}

void downLeftCorner(int x, int y, bool _2Line)
{
    gotoXY(x, y);
    if (!_2Line) cout << (char)192;
    else cout << (char)200;
}

void downRightCorner(int x, int y, bool _2Line)
{
    gotoXY(x, y);
    if (!_2Line) cout << (char)217;
    else cout << (char)188;
}

void diagonalLine_DownRight(int x, int y, int length)
{
    for (int i = 0; i < length; i++)
    {
        gotoXY(x + i, y + i);
        cout << '\\';
    }
}

void diagonalLine_DownLeft(int x, int y, int length)
{
    for (int i = 0; i < length; i++)
    {
        gotoXY(x - i, y + i);
        cout << '/';
    }
}

void table(int x, int y, int cols, int rows, int colWidth, int rowHeight, bool _2Line)
{
    rectangleBorder(x, y, rows * (rowHeight + 1) + 1, cols * (colWidth + 1) + 1, _2Line);

    for (int i = 1; i < cols; i++)
        verticalLine(x + i * (colWidth + 1), y + 1, rows * (rowHeight + 1) - 1, _2Line);

    for (int i = 1; i < rows; i++)
        horizontalLine(x + 1, y + i * (rowHeight + 1), cols * (colWidth + 1) - 1, _2Line);

    for (int i = 1; i < cols; i++)
    {
        tShapeDown(x + i * (colWidth + 1), y, _2Line);
        tShapeUp(x + i * (colWidth + 1), y + rows * (rowHeight + 1), _2Line);
    }

    for (int i = 1; i < rows; i++)
    {
        tShapeRight(x, y + i * (rowHeight + 1), _2Line);
        tShapeLeft(x + cols * (colWidth + 1), y + i * (rowHeight + 1), _2Line);
    }

    for (int i = 1; i < rows; i++)
    {
        for (int j = 1; j < cols; j++)
        {
            crossShape(x + j * (colWidth + 1), y + i * (rowHeight + 1), _2Line);
        }
    }
}
