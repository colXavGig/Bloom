#include "Navigation.h"

Navigation::Navigation(GardenPath* path):gardenpath(path), currentPath(path->getRoot().string()){}

std::vector<char> Navigation::loadFileContent(const std::string& fileHash){
    std::vector<char> content;
    fs::path filePath = gardenpath->getFlowerPath(fileHash);

    std::ifstream in(filePath, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Failed to open seed file: " + filePath.string());
    }

    //trouver la taille du fichier
    in.seekg(0, std::ios::end);
    size_t size = in.tellg();
    in.seekg(0, std::ios::beg);

    content.resize(size);
    in.read(content.data(), size);

    in.close();
    return content;
}

void Navigation::walk(const std::string& treeHash, WalkCallback callback, void* context) {
    walkFolder(treeHash, "", callback,context);  
}

void Navigation::walkFolder(const std::string& folderHash, const std::string& path, WalkCallback callback, void* context) {

    std::filesystem::path folderPath = gardenpath->getFlowerPath(folderHash);

    std::ifstream in(folderPath, std::ios::binary);
    if (!in) {
        throw std::runtime_error("folder non existant " + folderPath.string());
    }

    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) {
            if (line.compare(0, 11, "[FOLDERNAME]") == 0) {
                continue; 
            }
            char* c_line = &line[0];
            MetaDataFOS_S entry = MetaDataFOS_init(c_line);
            std::string fullPath = path + "/" + entry.fosname;
            callback(&entry, fullPath, context);
            if (strcmp(entry.fostype,"[FOLDER]")==0) {
                walkFolder(entry.signature, fullPath, callback,context);
            }
        }       
    }
}
