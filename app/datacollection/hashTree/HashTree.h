#pragma once
#include <iostream>
#include "HashNode.h"

using namespace std;
namespace  fs =  std::filesystem;
/**
 * Agence les nodes de manieres qu'elles imitent le filsystem
 * Sa responsabilite: creer un tree avec la class HashNodes
 *
 * 1 propriete le root du Tree
*/
class HashTree {
    public:
        HashTree(FolderNode *root);
        void listBranches(FolderNode* parent);

        FolderNode* getRoot() const {
            return this->root;
        }

    private:
        FolderNode *root;    
        void createProjectTree(FolderNode *parentNode);
        void createGardenTree(FolderNode *parentNode);
 };