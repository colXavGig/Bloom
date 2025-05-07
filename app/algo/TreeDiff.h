#pragma once

#include "../GardenNavigation/Navigation.h"
#include "../FOS/FOS_metadata.h"
#include "diff.h"
#include <unordered_map>
#include <string>
#include <vector>
typedef void (*WalkCallback)(FOS_metadata* entry, std::string fullPath);

class TreeDiff{
    private:
        Navigation nav;
        std::unordered_map<std::string, FOS_metadata*> headMap;
        std::unordered_map<std::string, FOS_metadata*> targetMap;
        Diff result;

        static void addToMap(std::unordered_map<std::string, FOS_metadata*> map,FOS_metadata* entry, std::string fullPath){map[path] = new FOS_metadata(*meta);};
    public:
        void buildMap(const std::string& hash, std::unordered_map<std::string, FOS_metadata*>& map);

        void compareTrees(std::string& headHash, std::string& targetHash);

        Diff& getDiff() { return result; };
        
    };