#include "fileBuilder.h"
#define LOGGING_STATUS LOGGER_ACTIVE
#include "../debugging.h"



FileBuilder::FileBuilder(GardenPath* path): gardenpath(path),nav(gardenpath){}


void FileBuilder::build(const std::string& treeHash) {
    nav.walk(treeHash, fileBuilderCallback,this);  
}

void FileBuilder::fileBuilderCallback(MetaDataFOS_S* entry, const std::string& fullPath, void* context) {
    FileBuilder* builder = static_cast<FileBuilder*>(context);
    
    LOG((""));LOG((""));
    LOG(("----- BUILD STEP -----"));
    LOG(("Type: " + std::string(entry->fostype)).c_str());
    LOG(("Name: " + std::string(entry->fosname)).c_str());
    LOG(("Signature: " + std::string(entry->signature)).c_str());
    LOG(("Full path: " + fullPath).c_str());
    LOG((""));LOG((""));

    if (strcmp(entry->fostype, "[FOLDER]") == 0) {
        std::filesystem::create_directories(fullPath);
    } else {
        std::filesystem::path filePath = builder->gardenpath->getFlowerPath(entry->signature);

        std::ifstream in(filePath, std::ios::binary);
        if (!in) {
            throw std::runtime_error("Failed to open seed file: " + filePath.string());
        }

        in.seekg(0, std::ios::end);
        size_t size = in.tellg();
        in.seekg(0, std::ios::beg);

        std::vector<char> content(size);
        in.read(content.data(), size);

        std::ofstream out(fullPath, std::ios::binary);
        if (!out) {
            throw std::runtime_error("Failed to create output file: " + fullPath);
        }
        out.write(content.data(), size);
    }
}