#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "../FOS/FOS_metadata.h"
#include "../GardenNavigation/Navigation.h"

#include "../paths/GardenPath.h"
#include "../fileSystemManagement/utilz/PathManagement/StaticPath.h"




class FileBuilder {
    private:
        Navigation nav;
    
    public:
        void reset();
        void build(const std::string& treeHash);
    };