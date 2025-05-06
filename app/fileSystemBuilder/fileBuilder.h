#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "../FOS/FOS_metadata.h"
#include "../GardenNavigation/Navigation.h"

#include "../paths/GardenPath.h"
#include "../fileSystemManagement/utilz/PathManagement/StaticPath.h"


typedef void (*WalkCallback)(FOS_metadata* entry, std::string fullPath);


class FileBuilder {
    private:
        Navigation nav;
        // Static callback for Navigation
        static void fileBuilderCallback(FOS_metadata* entry, std::string fullPath);
    
    public:
        void reset();
        void build(const std::string& treeHash);
    };