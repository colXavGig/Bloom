#include "TreeDiff.h"

void TreeDiff::buildMap(const std::string& hash, std::unordered_map<std::string, FOS_metadata*>& map) {
    nav.walk(hash, addToMap);
}
void TreeDiff::addToMap(FOS_metadata* entry, std::string fullPath){


};


void TreeDiff::compareTrees(std::string& headHash, std::string& targetHash) {
    buildMap(headHash, headMap);
    buildMap(targetHash, targetMap);

    for (const auto& [path, hmeta] : headMap) {
        auto it = targetMap.find(path);
        if (it == targetMap.end()) {
            result.REMOVED(hmeta->toFILE_S());
        } else {
            auto tmeta = it->second;
            if (!hmeta->isEqual(tmeta)) {
                result.MODIFIED(hmeta->toFILE_S());
            }
            targetMap.erase(it);
        }
    }

    for (const auto& [path, tmeta] : targetMap) {
        result.ADDED(tmeta->toFILE_S());
    }
} 