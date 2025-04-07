#include "../datacollection/hashTree/HashNode.h"
#include "../datacollection/hashTree/HashTree.h"
#include <iostream>
#include <string>
class HashTree;
using namespace std;

/**
 * class that holds the data to point to a commit of an Hashtree
 */
class GardenTag{

public:
    string message;
    time_t timestamp;

    /**
     * Construct a GardenTag with the specified roo
     * @param tree the tree that the tag should point to
     * @param msg the message recorded by the user to explain the changed in the repo
     */
    GardenTag(HashTree *tree, string msg):root()
    {
        setRoot(tree->getRoot());
        timestamp = time(NULL);
        this->message = msg;
        generateSignature();
    };

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
    FolderNode* getRoot(){
        return this->root;
    }


    private:
        FolderNode* root;
        string signature;

        void setRoot(HashNode *root);
        void generateSignature();
};