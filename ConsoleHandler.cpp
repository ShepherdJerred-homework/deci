#include <iostream>
#include <string>
#include <windows.h>
#include "ConsoleHandler.h"

ConsoleHandler::ConsoleHandler() {}

ConsoleHandler::ConsoleHandler(short headerRows, short footerRows) {

    // http://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns

    console = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(console, &csbi);
    rows = (short) (csbi.srWindow.Right - csbi.srWindow.Left + 1);
    columns = (short) (csbi.srWindow.Bottom - csbi.srWindow.Top);

    COORD maxPosition;
    maxPosition.X = rows;
    maxPosition.Y = columns;
    this->maxPosition = maxPosition;

    std::cout << rows;
    std::cout << columns;

    this->headerRows = headerRows;
    this->footerRows = footerRows;

    SetConsoleScreenBufferSize(console, maxPosition);
};

void ConsoleHandler::clearScreen() {
    setCursorPosition(0, 0);
    for (int x = 0; x < maxPosition.X; x++) {
        for (int y = 0; y < maxPosition.Y + 1; y++) {
            std::cout << " ";
        }
    }
}

void ConsoleHandler::moveCursorInDirection(Direction direction) {
    switch (direction) {
        case UP:
            moveCursor(getCursorPosition().X, (short) (getCursorPosition().Y - 1));
            break;
        case DOWN:
            moveCursor(getCursorPosition().X, (short) (getCursorPosition().Y + 1));
            break;
        case LEFT:
            moveCursor((short) (getCursorPosition().X - 1), getCursorPosition().Y);
            break;
        case RIGHT:
            moveCursor((short) (getCursorPosition().X + 1), getCursorPosition().Y);
            break;
    }
}

void ConsoleHandler::moveCursorToStart() {
    // Move it to the absolute top first so we're sure the header is visible
    moveCursorWithoutChecks(0, 0);
    moveCursorWithoutChecks(0, 1);
}

void ConsoleHandler::moveCursor(short x, short y) {
    if (x >= 0 &&
        x <= this->maxPosition.X &&
        y >= 0 &&
        y <= this->maxPosition.Y &&
        y > headerRows - 1 &&
        y < this->maxPosition.Y - footerRows - 1) {
        setCursorPosition(x, y);
    }
}

void ConsoleHandler::moveCursorWithoutChecks(short x, short y) {
    setCursorPosition(x, y);
}

void ConsoleHandler::setCursorPosition(short x, short y) {
    COORD newPosition;
    newPosition.X = x;
    newPosition.Y = y;
    getCursorPosition() = newPosition;
    SetConsoleCursorPosition(this->console, newPosition);
}

COORD ConsoleHandler::getMaxPosition() {
    return maxPosition;
}

COORD ConsoleHandler::getCursorPosition() {
    GetConsoleScreenBufferInfo(console, &csbi);
    return csbi.dwCursorPosition;
}

short ConsoleHandler::getHeaderRows() {
    return headerRows;
}

short ConsoleHandler::getFooterRows() {
    return footerRows;
}
