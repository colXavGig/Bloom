#include "Navigation.h"
#include <iostream>
#define LOGGING_STATUS LOGGER_ACTIVE
#include "../debugging.h"
Navigation::Navigation(GardenPath* path):gardenpath(path), currentPath(path->getRoot().string()){}


void Navigation::walk(const std::string& treeHash, WalkCallback callback, void* context) {
    walkFolder(treeHash, "", callback,context);  
}


void Navigation::walkFolder(const std::string& folderHash, std::string path, WalkCallback callback, void* context) {
    std::filesystem::path folderPath = gardenpath->getFlowerPath(folderHash);
    std::ifstream ifs(folderPath, std::ios::binary);
    if (!ifs) {
       
        throw std::runtime_error("folder non existant " + folderPath.string());
    }
    std::string line;
    while (std::getline(ifs, line)) {
        std::cout<<line<<"\n";
        if (!line.empty()) {
            try {
                if (line.compare(0, 12, "[FOLDERNAME]") == 0)continue; 
                FOS_metadata *entry = new FOS_metadata(line);
                std::string nextPath = path.empty() ? entry->getName() : (path + "/" + entry->getName());

                callback(entry, nextPath, context);
                if (entry->getType() == "[FOLDER]") {
                    walkFolder(entry->getHash(), nextPath, callback, context);
                }

            } catch (const std::runtime_error& e) {
                std::cerr << "Skipping corrupted line: " << line << "\n" << e.what() << std::endl;
            }
        }       
    }
}
