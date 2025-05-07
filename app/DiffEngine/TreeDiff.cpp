#include "TreeDiff.h"

void TreeDiff::buildMap(const std::string& hash, std::unordered_map<std::string, FOS_metadata*>& map) {
    nav.walk(hash, [&](FOS_metadata* meta, std::string fullpath) {
        map[fullpath]= new FOS_metadata(*meta);
    });
}



void TreeDiff::compareTrees(std::string& headHash, std::string& targetHash) {
    buildMap(headHash, headMap);
    buildMap(targetHash, targetMap);

    for (const auto& [path, hmeta] : headMap) {
        auto it = targetMap.find(path);
        if (it == targetMap.end()) {

            result.REMOVED(Block(0, 0, path, ""));
        } else {
            auto tmeta = it->second;
            if (!hmeta->isHashEqual(*tmeta)) {
                Juxtapose juxtapose;
                juxtapose.parseMetadata(hmeta->getHash(), tmeta->getHash(), path);

                Diff blockDiff = juxtapose.getroot();
                result.merge(blockDiff); 
            }
            targetMap.erase(it);
        }
    }

    for (const auto& [path, tmeta] : targetMap) {
        result.ADDED(Block(0, 0, path, ""));
    }
} 

