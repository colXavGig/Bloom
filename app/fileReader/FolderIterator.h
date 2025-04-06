#include <iostream>
#include <fstream>
#include "../paths/GardenPath.h"

class FolderIterator{
    private:
        GardenPath path = GardenPath(".");
        std::ifstream *ifs;
        std::string token;
        std::string signature;
        std::string filename;
    
    public:
        FolderIterator(std::string signature);
        bool Next();
        std::string getToken();
        std::string getSignature();
        std::string getFilename();
};
