#ifndef DECI_FILEMANAGER_H
#define DECI_FILEMANAGER_H

bool operator<(COORD, COORD);

class FileManager {
public:
    void writeToFile(std::string fileName, std::string text);

    std::map<COORD, char> readFromFile(std::string fileName);
};


#endif //DECI_FILEMANAGER_H
