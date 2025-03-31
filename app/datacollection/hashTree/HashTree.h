#pragma once
#include <iostream>
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
        FolderNode *root;    
        void createTree(FolderNode *parentNode);
    public:
        HashTree(FolderNode *root);

        void listBranches(FolderNode* parent);

        FolderNode* getRoot() {
            return this->root;
        }

 };