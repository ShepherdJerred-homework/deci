#ifndef DECI_EDITOR_H
#define DECI_EDITOR_H

#include <map>
#include <windows.h>
#include "ConsoleHandler.h"

class Editor {

private:

    std::map<COORD, char> text;

    std::string filename;

    ConsoleHandler consoleHandler;

    void printEditorFooter();

    void listenForKeys();

    bool keyIsPressed(int key);

    void setCharacter(COORD, char);

    void printEditorHeader();

    void initializeMap();

public:
    Editor(ConsoleHandler consoleHandler, std::string filename);

    void start(std::string);

    std::string getText();

    Editor(ConsoleHandler consoleHandler, std::string filename, std::map<COORD, char> text);
};


#endif //DECI_EDITOR_H
