#include "Editor.h"
#include "FileManager.h"
#include <iostream>
#include <vector>
#include <string>

Editor::Editor(ConsoleHandler consoleHandler, std::string filename, std::map<COORD, char> text) {
    this->filename = filename;
    this->consoleHandler = consoleHandler;
    this->text = text;
    initializeMap();
}

Editor::Editor(ConsoleHandler consoleHandler, std::string filename) {
    this->filename = filename;
    this->consoleHandler = consoleHandler;
    initializeMap();
}

void Editor::start(std::string filename) {
    consoleHandler.clearScreen();

    printEditorHeader();
    printEditorFooter();

    consoleHandler.moveCursorToStart();

    listenForKeys();
}

void Editor::printEditorHeader() {
    consoleHandler.moveCursorWithoutChecks(0, 0);
    std::cout << "deci              Filename: " << filename;
}

void Editor::printEditorFooter() {
    consoleHandler.moveCursorWithoutChecks(0, consoleHandler.getMaxPosition().Y);
    std::cout << "Save: CTRL        Close: ESC";
}

void Editor::listenForKeys() {
    while (true) {
        if (keyIsPressed(VK_UP)) {
            consoleHandler.moveCursorInDirection(UP);
        }
        if (keyIsPressed(VK_DOWN)) {
            consoleHandler.moveCursorInDirection(DOWN);
        }
        if (keyIsPressed(VK_LEFT)) {
            consoleHandler.moveCursorInDirection(LEFT);
        }
        if (keyIsPressed(VK_RIGHT)) {
            consoleHandler.moveCursorInDirection(RIGHT);
        }

        if (keyIsPressed(VK_CONTROL)) {
            FileManager fileManager;
            fileManager.writeToFile(filename, getText());
        }
        if (keyIsPressed(VK_ESCAPE)) {
            // Exit Editor
            break;
        }
        if (keyIsPressed(VK_BACK)) {
            if (consoleHandler.getCursorPosition().X == 0) {
                consoleHandler.moveCursorInDirection(UP);
            } else {
                consoleHandler.moveCursorInDirection(LEFT);
                std::cout << " ";
                consoleHandler.moveCursorInDirection(LEFT);
            }
        }
        if (keyIsPressed(VK_RETURN)) {
            consoleHandler.moveCursorInDirection(DOWN);
        }
        // Print the character
        // Check 0-9
        for (int i = 48; i < 57; i++) {
            if (keyIsPressed(i)) {
                std::cout << (char) i;
                setCharacter(consoleHandler.getCursorPosition(), (char) i);
            }
        }
        // Check a-z
        for (int i = 41; i < 90; i++) {
            if (keyIsPressed(i)) {
                std::cout << (char) i;
                setCharacter(consoleHandler.getCursorPosition(), (char) i);
            }
        }
        // Check space
        if (keyIsPressed(VK_SPACE)) {
            std::cout << " ";
            setCharacter(consoleHandler.getCursorPosition(), ' ');
        }

    }
}

bool Editor::keyIsPressed(int key) {
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms646293(v=vs.85).aspx
    const int LEAST_SIGNIFICANT_BIT = 1;

    if (GetAsyncKeyState(key) & LEAST_SIGNIFICANT_BIT) {
        return true;
    } else {
        return false;
    }
}

void Editor::setCharacter(COORD coord, char character) {
    text[coord] = character;
}

void Editor::initializeMap() {
    for (short x = 0; x < consoleHandler.getMaxPosition().X; x++) {
        for (short y = 0; y < consoleHandler.getMaxPosition().Y; y++) {
            COORD coord;
            coord.X = x;
            coord.Y = y;
            // http://stackoverflow.com/questions/3886593/how-to-check-if-stdmap-contains-a-key-without-doing-insert
            if (text.find(coord) != text.end()) {
                text[coord] = ' ';
            }
        }
    }
}

std::string Editor::getText() {
    std::string returnString = "";

    for (short y = 0; y < consoleHandler.getMaxPosition().Y; y++) {
        if (y < consoleHandler.getHeaderRows()) {
            continue;
        }

        if (y > consoleHandler.getMaxPosition().Y - consoleHandler.getFooterRows()) {
            break;
        }

        for (short x = 0; x < consoleHandler.getMaxPosition().X; x++) {
            COORD coord;
            coord.X = x;
            coord.Y = y;
            returnString += text[coord];
        }
        returnString += '\n';
    }

    return returnString;
}
