//
// Created by bebew on 2025-03-25.
//

#include "GardenPath.h"
using namespace std;
namespace fs = std::filesystem;

fs::path GardenPath::getIndexFilepath() {
    return getGardenPath() / "index";
  }
  
GardenPath::GardenPath(string root) {
    this->root = fs::path(root);
}

fs::path GardenPath::getRoot() {
    return this->root;
}

fs::path GardenPath::getGardenPath() {
    return root / ".garden";
}

fs::path GardenPath::getSeedPath() {
    return getGardenPath() / "seeds";
}

fs::path GardenPath::getTagPath() {
    return getGardenPath() / "tag";
}

fs::path GardenPath::getFlowerPath(std::string signature){
    return getSeedPath() / signaturePath(signature);
}

fs::path GardenPath::getGardenTagPath(std::string signature){
    return getTagPath() / signaturePath(signature);
}


std::string GardenPath::signaturePath(std::string signature){
    std::string folder="",file="";
    for(int i = 0; i<signature.size(); i++){
        if(i < 2){ folder += signature[i]; continue; }
        file += signature[i];
    }   
    return  (folder+"/"+file);
}

