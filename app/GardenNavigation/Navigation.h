#include <vector>
#include "stdio.h"
#include "../paths/GardenPath.h"
#include "../algo/FOS/MetaData.h"
#include <vector>
#include <fstream>
typedef void (*WalkCallback)(MetaDataFOS_S* entry, const std::string& fullPath, void* context);

class Navigation{
    private:
        GardenPath *gardenpath;
        std::string currentPath;
        std::vector<char> loadFileContent(const std::string& fileHash);
         
    public:
        Navigation(GardenPath* path);
        ~Navigation();
    void walk(const std::string& treeHash, WalkCallback callback, void *context);
    void walkFolder(const std::string& folderHash, const std::string& path, WalkCallback callback, void *context);
};