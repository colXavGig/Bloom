#pragma once
#include <iostream>
#include <filesystem>
#include "HashNode.h"
#include "../../processes/Hashing.h"
using namespace std;
namespace  fs =  std::filesystem;
/*
Agence les nodes de manieres qu'elles imitent le filsystem
Sa responsabilite: creer un tree avec la class HashNodes

1 propriete le root du Tree
*/
class HashTree{
    private:
        HashNode root;
        fs::path fsdirectory;
        
        void createTree(HashNode *pnode,fs::path directory);
    public:
        HashTree(fs::path directory);

        void printTree(HashNode* node, int depth = 0);

        HashNode* getRoot() {
            return &this->root;
        }

 };