#include "GardenTag.h"

#include "../processes/tag_hashing.cpp"
using namespace std;


        
//setters
string GardenTag::getHash() {

    return signature;
}

string GardenTag::getRootHash() {
    return this->root->getSignature();
}
string GardenTag::getMessage() {
  return this->message;
}

/////////////////////////////////////////////
///                PRIVATE                ///
/////////////////////////////////////////////

void GardenTag::setRoot(FolderNode *root) {
  this->root = root;
}

void GardenTag::generateSignature() {
  unsigned char hash[HASH_SIZE];
    tagHashing(this, &hash);
    string hashStr = to_string(hash[0]);
    for(int i=1; i < HASH_SIZE; i++) {
      hashStr += to_string(hash[i]);
    }
    this->signature = hashStr;
}

