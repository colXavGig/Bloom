#include "../paths/GardenPath.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "../algo/FOS/MetaData.h"
#include "../GardenNavigation/Navigation.h"

typedef void (*WalkCallback)(MetaDataFOS_S* entry, const std::string& fullPath, void* context);
class FileBuilder {
    private:
        GardenPath* gardenpath;
        Navigation nav;
    
        // Static callback for Navigation
        static void fileBuilderCallback(MetaDataFOS_S* entry, const std::string& fullPath, void* context);
    
    public:
        FileBuilder(GardenPath* path);
    
        void build(const std::string& treeHash);
    };