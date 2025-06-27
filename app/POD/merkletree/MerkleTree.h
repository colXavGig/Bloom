#pragma once

#include <iostream>

#include "HashNode.h"
#include "../../POD/gardentag/c/GardenTag_struct.h"

using namespace std;
/**
 * Agence les nodes de manieres qu'elles imitent le filsystem
 * Sa responsabilite: creer un tree avec la class HashNodes
 *
 * 1 propriete le root du Tree
*/
class MerkleTree {
    public:
        MerkleTree(FolderNode *root);
        void listBranches(FolderNode* parent);

        FolderNode* get_root() const {
            return root;
        }

    private:
        FolderNode *root;
        void create_merkle_tree(FolderNode *parentNode);
};
