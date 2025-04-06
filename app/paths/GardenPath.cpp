//
// Created by bebew on 2025-03-25.
//

#include "GardenPath.h"
using namespace std;
namespace fs = std::filesystem;




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
