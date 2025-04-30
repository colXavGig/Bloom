#include "../paths/GardenPath.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "../FOS/FOS_metadata.h"
#include "../GardenNavigation/Navigation.h"

typedef void (*WalkCallback)(FOS_metadata* entry, std::string fullPath, void* context);


class FileBuilder {
    private:
        GardenPath* gardenpath;
        Navigation nav;
    
        // Static callback for Navigation
        static void fileBuilderCallback(FOS_metadata* entry, std::string fullPath, void* context);
    
    public:
        FileBuilder(GardenPath* path);
        void reset();
        void build(const std::string& treeHash);
    };