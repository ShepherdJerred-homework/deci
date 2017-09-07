#include <iostream>
#include "StartMenu.h"

void showStartMenu() {
    ConsoleHandler consoleHandler(1,1);
    StartMenu startMenu(consoleHandler);
    startMenu.start();
}

int main() {
    showStartMenu();
    system("pause");
    return 0;
}
