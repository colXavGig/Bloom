#include "GardenTag.h"

#include "../processes/tag_hashing.cpp"
using namespace std;


        
//setters
string GardenTag::getHash() {

    return value->signature;
}

string GardenTag::getRootHash() {
    return value->root->signature;
}
string GardenTag::getMessage() {
  return value->message;
}

GardenTag_s *GardenTag::getStructValue() {
  return value;
}

/////////////////////////////////////////////
///                PRIVATE                ///
/////////////////////////////////////////////

void GardenTag::setRoot(FolderNode *root) {
  value->root = root->getStructValue();
}

void GardenTag::generateSignature() {
  unsigned char hash[HASH_SIZE];
    tagHashing(value, &hash);
    string hashStr = to_string(hash[0]);
    for(int i=1; i < HASH_SIZE; i++) {
      hashStr += to_string(hash[i]);
    }
    value->signature = hashStr.data();
}

