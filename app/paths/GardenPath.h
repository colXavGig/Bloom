//
// Created by bebew on 2025-03-25.
//

#ifndef GARDENPATH_H
#define GARDENPATH_H
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

class GardenPath {
    private:
        fs::path root;
    public:
        GardenPath(string root);
        fs::path getRoot();
        fs::path getGardenPath();
        fs::path getSeedPath();
<<<<<<< HEAD
        fs::path getGrowthPath();
        fs::path getFlowerPath(std::string signature);
=======
        fs::path getTagPath();
>>>>>>> 57c66847cdbd5f591c25e3e78601257cc47bbdde
};



#endif //GARDENPATH_H
