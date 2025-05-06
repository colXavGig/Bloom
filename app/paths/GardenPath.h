//
// Created by bebew on 2025-03-25.
//

#ifndef GARDENPATH_H
#define GARDENPATH_H
#include <filesystem>


namespace fs = std::filesystem;

class GardenPath {
    private:
        fs::path root;
    public:
        GardenPath(std::string root);
        fs::path getRoot();
        fs::path getGardenPath();
        fs::path getSeedPath();
        fs::path getTagPath();

        fs::path getFlowerPath(std::string signature);
        fs::path getGardenTagPath(std::string signature);
        fs::path getIndexFilepath();

        static std::string _signaturePath(std::string signature);
        fs::path getTestingPath();
};



#endif //GARDENPATH_H
