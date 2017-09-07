#ifndef DECI_CONSOLEHANDLER_H
#define DECI_CONSOLEHANDLER_H

#include <cstdlib>
#include <windows.h>

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

class ConsoleHandler {

private:
    COORD maxPosition;
    HANDLE console;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    short rows, columns;
    short headerRows, footerRows;

    void setCursorPosition(short, short);

public:
    ConsoleHandler(short, short);

    ConsoleHandler();

    void clearScreen();

    void moveCursorInDirection(Direction);

    void moveCursorWithoutChecks(short, short);

    void moveCursorToStart();

    void moveCursor(short, short);

    COORD getMaxPosition();

    COORD getCursorPosition();

    short getHeaderRows();

    short getFooterRows();
};

#endif //DECI_CONSOLEHANDLER_H
