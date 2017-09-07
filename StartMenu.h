#ifndef DECI_STARTMENU_H
#define DECI_STARTMENU_H


#include "ConsoleHandler.h"

class StartMenu {

private:
    ConsoleHandler consoleHandler;
    void listenForInput();
    void printMenu();

public:
    StartMenu(ConsoleHandler);
    void start();

};


#endif //DECI_STARTMENU_H
