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
        fs::path getGrowthPath();
        fs::path getFlowerPath(std::string signature);
};



#endif //GARDENPATH_H
