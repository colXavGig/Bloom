#pragma once

#include <iostream>
#include <string>

#include "GardenTag_struct.h"
#include "../datacollection/hashTree/HashNode.h"
#include "../datacollection/hashTree/HashTree.h"

using namespace std;
namespace  fs =  std::filesystem;



/**
 * class that holds the data to point to a commit of an Hashtree
 */
class GardenTag{

public:
    /**
     * Construct a GardenTag with the specified roo
     * @param tree the tree that the tag should point to
     * @param msg the message recorded by the user to explain the changed in the repo
     */
    GardenTag(HashTree *tree, string msg)
    {
        value = new GardenTag_s();
        setRoot(tree->getRoot());
        setMessage(msg);
        value->timestamp = time(NULL);
        generateSignature();
    };

    GardenTag(GardenTag_s *value) {
      this->value = value;
    }

    /**
     * gets the hashed signature generated by the tag
     * @return the hash of the tag
     */
    string getHash();
    /**
     * get the signature of the root of the HashTree
     * @return the signature of the root of the HashTree
     */
    string getRootHash();

    string getMessage();
    string getTimestamp();
    FolderNode* getRoot(){
        return new FolderNode(value->root);
    }

    GardenTag_s *getStructValue();

    operator GardenTag_s *() const {
        return  value;
    }


    private:
        GardenTag_s *value;

        void setRoot(FolderNode *root);
        void generateSignature();
        void setSignature(string signature);
        void setMessage(string message);
};