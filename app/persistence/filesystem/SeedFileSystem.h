#include <stdexcept>
#include <filesystem>
#include "../../POD/merkletree/MerkleTree.h"

#include "../../utils/path/StaticPath.h"
#include "../../utils/path/GardenPath.h"

namespace fs = std::filesystem;


class SeedFileSystem{
  public:
    SeedFileSystem();

    MerkleTree *read_heap(GardenPath seed_path);
    //writes to gardenpath using an tree in the heap
    void write_heap(MerkleTree &tree);
    //reads lazily fs gradually builds tree
    HashNode *read_lazy(GardenPath seed_path);
    //writes while lazily navigating fs
    void write_lazy(GardenPath project_root);

  private:
    //const path to seed folder in garden 
    const fs::path seed_path = staticpath::_staticPath::_SEED(); 
     
};
