#include <iostream>
#include <fstream>
#include "../paths/GardenPath.h"

struct line{
    std::string buffer;
    int index;
};

class FileIterator {
    private:
        GardenPath path = GardenPath(".");
        std::ifstream *ifs; 
        line *Line;
    public:
        //constructor
        FileIterator(std::string path);

        //functions
        bool Next();
        std::string getLine();
        int getIndex();
};