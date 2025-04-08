#include "GardenTag.h"

#include "../processes/tag_hashing.cpp"

#define LOGGER_STATUS LOGGER_INACTIVE
#include "../debugging.h"

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

string GardenTag::getTimestamp() {
  return ctime(&value->timestamp);
}

GardenTag_s *GardenTag::getStructValue() {
  return value;
}

/////////////////////////////////////////////
///                PRIVATE                ///
/////////////////////////////////////////////

void GardenTag::setRoot(FolderNode *root) {
  LOG("Setting root...");
  value->root = root->getStructValue();
}

void GardenTag::generateSignature() {
    LOG("Generating signature...");
    value->signature = new char[41];
    tagHashing(value, (char(*)[41])value->signature);
    LOG("Signature generated!");
}

void GardenTag::setSignature(string signature) {
  LOG("Setting signature...");
  value->signature = new char[signature.length()+1];
  strcpy(value->signature, signature.c_str());
}

void GardenTag::setMessage(string message) {
  LOG("Setting message...");
  value->message = new char[message.length()+1];
  strcpy(value->message, message.c_str());
}

