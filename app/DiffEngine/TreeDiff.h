#pragma once

#include "../GardenNavigation/Navigation.h"
#include "../FOS/FOS_metadata.h"
#include "Diff.h"
#include "Juxtapose.h"
#include <unordered_map>
#include <string>
#include <vector>

class TreeDiff{
    private:
        Navigation nav;
        std::unordered_map<std::string, FOS_metadata*> headMap;
        std::unordered_map<std::string, FOS_metadata*> targetMap;
        Diff result;
        

    public:
        void buildMap(const std::string& hash, std::unordered_map<std::string, FOS_metadata*>& map);

        void compareTrees(std::string& headHash, std::string& targetHash);

        Diff& getDiff() { return result; };
        
    };