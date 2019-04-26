#ifndef CONSOLE_H
#define CONSOLE_H

void gotoXY(int x, int y);
void clearScreen();
void setWindowFullscreen(char name[]);
void setWindow(int width, int height, char name[]);
void changeColor(int color);

void rectangleBorder(int x, int y, int height, int width, bool _2Line = false);
void horizontalLine(int x, int y, int length, bool _2Line = false);
void verticalLine(int x, int y, int length, bool _2Line = false);
void tShapeUp(int x, int y, bool _2Line = false);
void tShapeDown(int x, int y, bool _2Line = false);
void tShapeLeft(int x, int y, bool _2Line = false);
void tShapeRight(int x, int y, bool _2Line = false);
void crossShape(int x, int y, bool _2Line = false);
void upLeftCorner(int x, int y, bool _2Line = false);
void upRightCorner(int x, int y, bool _2Line = false);
void downLeftCorner(int x, int y, bool _2Line = false);
void downRightCorner(int x, int y, bool _2Line = false);
void table(int x, int y, int cols, int rows, int colWidth, int rowHeight, bool _2Line = false);

#endif //CONSOLE_H
