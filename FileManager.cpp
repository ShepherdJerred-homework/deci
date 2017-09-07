#include <string>
#include <fstream>
#include <windows.h>
#include <map>
#include "FileManager.h"

bool operator<(COORD lValue, COORD rValue) {
    // http://stackoverflow.com/questions/18019975/make-an-stdmap-with-a-coordinate-as-key
    if (lValue.Y < rValue.Y) {
        return true;
    } else if (rValue.Y < lValue.Y) {
        return false;
    }
    return lValue.X < rValue.X;
}

void FileManager::writeToFile(std::string fileName, std::string text) {
    std::ofstream file;
    file.open(fileName);
    file << text;
    file.close();
}

std::map<COORD, char> FileManager::readFromFile(std::string fileName) {
    std::map<COORD, char> map;
    std::ifstream file(fileName);
    std::string currentLine;
    if (file.is_open()) {
        short x = 0;
        short y = 0;
        while (getline(file, currentLine)) {
            for (std::string::size_type i = 0; i < currentLine.size(); i++) {
                COORD position;
                position.X = x;
                position.Y = y;
                map[position] = (char) currentLine[i];
                x++;
            }
            y++;
        }
    }
    return map;
}
