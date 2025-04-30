#include "fileBuilder.h"
#define TESTINGPATH "app\\testing\0"
#define LOGGING_STATUS LOGGER_ACTIVE
#include "../debugging.h"
#define LOG_PATH(p) LOG((std::filesystem::absolute(p)).string().c_str())
#include <iostream>

FileBuilder::FileBuilder(GardenPath* path): gardenpath(path),nav(gardenpath){}


void FileBuilder::build(const std::string& treeHash) {
    nav.walk(treeHash, fileBuilderCallback,this);  
}

void FileBuilder::fileBuilderCallback(FOS_metadata* entry, std::string fullPath, void* context) {
std::cout<< fullPath;
    FileBuilder* builder = static_cast<FileBuilder*>(context);

    fs::path dest = fs::absolute(fs::path("app\\testing")/fullPath).lexically_normal();
    std::cout << "Creating: " << dest << std::endl;
    if (entry->getType() == "[FOLDER]") {
        fs::create_directories(dest);
    } 
    
    else if (entry->getType() == "[FILE]"){

        fs::path filePath = builder->gardenpath->getFlowerPath(entry->getHash());
        filePath = fs::absolute(filePath.lexically_normal().make_preferred());
        std::cout << "Creating: " << filePath << std::endl;
        fs::create_directories(dest.parent_path());
        if (fs::exists(filePath)) {
            fs::copy(filePath, dest, fs::copy_options::overwrite_existing);
        } else {

            std::cerr << "Missing file in garden store: " << filePath << std::endl;
        }
        std::cout <<"here";
    }
}

void FileBuilder::reset(){
    for (const auto& entry : fs::directory_iterator(TESTINGPATH)) {
        if (entry.path().filename() == ".garden") {
            continue;
        }
        std::error_code ec; 
        fs::remove_all(entry.path(), ec);

        if (ec) {
            printf("Failed to delete: %s, error: %s\n", entry.path().string().c_str(), ec.message().c_str());
        } else {
            printf("Deleted: %s\n", entry.path().string().c_str());
        }
    }
}
