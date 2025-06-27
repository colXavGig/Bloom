#include "SeedFileSystem.h"
#include <filesystem>

namespace fs = std::filesystem;
namespace helper {
  void static _DFS(FolderNode *node){
    while() 

  }
}
/*
 * writes in garden with a tree in the heap 
 * */
void SeedFileSystem::write_heap(MerkleTree &tree){
  fs::path flower_path = seed_path / tree.get_root()->get_signature();
  if(fs::exists(flower_path))
    throw std::logic_error("this version already exists");
  
  helper::_DFS(tree.get_root());
 
}
/*
 * reads from garden and makes a tree in the heap
 * */
MerkleTree SeedFileSystem::read_heap(){


}
void SeedFileSystem::write_lazy(GardenPath path){
  throw new std::logic_error("not implemented yet");

}

MerkleTree *SeedFileSystem::read_lazy(){
  throw new std::logic_error("not implemented yet");

}


