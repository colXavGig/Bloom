#include <vector>
#include "stdio.h"
#include "../paths/GardenPath.h"
#include "../FOS/FOS_metadata.h"
#include <vector>
#include <fstream>
typedef void (*WalkCallback)(FOS_metadata* entry, std::string fullPath, void* context);

class Navigation{
    private:
        GardenPath *gardenpath;
        std::string currentPath;
        std::vector<char> loadFileContent(const std::string& fileHash);
         
    public:
        Navigation(GardenPath* path);
        ~Navigation();
    void walk(const std::string& treeHash, WalkCallback callback, void *context);
    void walkFolder(const std::string& folderHash, std::string path, WalkCallback callback, void *context);
};