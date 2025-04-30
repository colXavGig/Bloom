#include "GardenTag.h"

#include "../processes/tag_hashing.cpp"

#define LOGGER_STATUS LOGGER_INACTIVE
#include "../debugging.h"

using namespace std;
using GP = gp::GardenProtocol;

        
//setters
string GardenTag::getHash() {
    return value->Hash;
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
  if (string(value->parentHash).empty())
    return "";
  return value->parentHash;
}
/////////////////////////////////////////////
///                PRIVATE                ///
/////////////////////////////////////////////

void GardenTag::setparentSignature(string parentHash){
  strncpy(value->parentHash, parentHash.c_str(), sizeof(value->parentHash) - 1);
  value->parentHash[40] ='\0';
}

void GardenTag::setRoot(FolderNode *root) {
  LOG("Setting root...");
  value->root = root->getStructValue();
}

void GardenTag::generateSignature() {
    LOG("Generating signature...");
    value->Hash = new char[41];
    tagHashing(value, (char(*)[41])value->Hash);
    LOG("Signature generated!");
}

void GardenTag::setSignature(string signature) {
  LOG("Setting signature...");
  value->Hash = new char[signature.length()+1];
  strcpy(value->Hash, signature.c_str());
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
    if(line.size()==0)break;
    vector<string> vec = GP::GardenDecode(line);
    if(vec.size()<2){
      throw runtime_error("invalid amount of data in GardenTag");
    }
    const std::string& tag = vec[0];
    
    if      (tag == "[PARENT]") setparentSignature(vec[1]);
    else if (tag == "[MSG]")    setMessage(vec[1]);
    else if (tag == "[TREE]")   setSignature(vec[1]);
    else throw std::runtime_error("Unrecognized tag in GardenTag: " + tag);
    }    
  }
