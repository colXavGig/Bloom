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

/**
 * DANGEROUS FUNCTION 
 * 
 * 
 * 
 */
string GardenTag::getparentSignature(){
  if (string(value->parent_signature).empty())
    return "";
  return value->parent_signature;
}
/////////////////////////////////////////////
///                PRIVATE                ///
/////////////////////////////////////////////

void GardenTag::setparentSignature(string parentSignature){
  strcpy(value->parent_signature, parentSignature.c_str());
}

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

GardenTag::GardenTag(fs::path path) {
  value = new GardenTag_s();
  std::ifstream in(path);

  if (!in) {
      throw std::runtime_error("Failed to open tag file: " + path.string());
  }
  std::string line;
  while (std::getline(in, line)) {
      if (line.rfind("[PARENT]", 0) == 0) {
          std::string content = line.substr(9); 
          setparentSignature(content);
      } else if (line.rfind("[MSG]", 0) == 0) {
          std::string content = line.substr(6);
          setMessage(content);
      } else if (line.rfind("[TREE]", 0) == 0) {
          std::string content = line.substr(7); 
          setSignature(content);
      }
  }
  cout << this->getHash()<<"\n";
};