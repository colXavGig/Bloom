#include "Navigation.h"
#include <iostream>
#define LOGGING_STATUS LOGGER_ACTIVE
#include "../debugging.h"





void Navigation::walk(const std::string& treeHash, WalkCallback callback) {
    walkFolder(treeHash, "", callback);  
}


void Navigation::walkFolder(const std::string& hash, std::string path, WalkCallback callback) {
   
    std::filesystem::path folderPath =SP::_SEEDROOT(hash);
    std::ifstream ifs(folderPath, std::ios::binary);
    if (!ifs) { 
        throw std::runtime_error("folder non existant " + folderPath.string());
    }
    std::string line;
    while (std::getline(ifs, line)) {

        if (!line.empty()) {
            try {
                if (line.compare(0, 12, "[FOLDERNAME]") == 0)continue; 
                FOS_metadata *entry = new FOS_metadata(line);
                std::string nextPath = path.empty() ? entry->getName() : (path + "/" + entry->getName());

                callback(entry, nextPath);
                if (entry->getType() == "[FOLDER]") {
                    walkFolder(entry->getHash(), nextPath, callback);
                }

            } catch (const std::runtime_error& e) {
                std::cerr << "Skipping corrupted line: " << line << "\n" << e.what() << std::endl;
            }
        }       
    }
}
