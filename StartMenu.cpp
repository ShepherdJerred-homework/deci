#include <iostream>
#include <vector>
#include <string>
#include "StartMenu.h"
#include "Editor.h"
#include "FileManager.h"

StartMenu::StartMenu(ConsoleHandler consoleHandler) {
    this->consoleHandler = consoleHandler;
}

void StartMenu::start() {
    printMenu();
    listenForInput();
}

void StartMenu::printMenu() {
    std::vector<std::string> options;

    options.push_back("Welcome to deci");
    options.push_back("1. Create new file");
    options.push_back("2. Open a file");
    options.push_back("3. Exit");

    consoleHandler.clearScreen();

    consoleHandler.moveCursorWithoutChecks(0, 0);

    for (std::size_t i = 0; i < options.size(); i++) {
        std::cout << options[i] << std::endl;
    }
}

void StartMenu::listenForInput() {
    char input;

    std::string fileName;

    do {
        std::cin >> input;
        switch (input) {
            case '1': {
                fileName = "new.txt";
                Editor editor(consoleHandler, fileName);
                editor.start(fileName);
                printMenu();
                break;
            }
            case '2': {
                // Open a file
                /* In here, we should do the following
                 * 1. Ask for a filename
                 * 2. Open the file
                 * 3. Set the editor's text to the files text
                 */
                FileManager fileManager;
                std::map<COORD, char> text = fileManager.readFromFile("new.txt");
                Editor editor(consoleHandler, fileName, text);
                editor.start(fileName);
                printMenu();
                break;
            }
            case '3':
                consoleHandler.clearScreen();
                consoleHandler.moveCursorToStart();
                std::cout << "Exiting deci";
                exit(0);
            default:
                std::cout << "Invalid option";
        }
    } while (input != '3');

}
