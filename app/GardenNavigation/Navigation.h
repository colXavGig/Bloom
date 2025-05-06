#include <vector>
#include "stdio.h"
#include <vector>
#include <fstream>
#include <functional>
#include "../paths/GardenPath.h"
#include "../FOS/FOS_metadata.h"

#include "../fileSystemManagement/utilz/PathManagement/StaticPath.h"
using SP = staticpath::_staticPath;



std::function<void(WalkCallback)> walkCallBack(FOS_metadata* entry, std::string fullPath);

class Navigation{
    private:
        std::string currentPath;
         
    public:
        ~Navigation();
    void walk(const std::string& treeHash, WalkCallback callback);
    void walkFolder(const std::string& folderHash, std::string path, WalkCallback callback);
};