#include "GardenTag.h"
#include "../utilz/processes/tag_hashing.cpp"


#define LOGGER_STATUS LOGGER_INACTIVE
#include "../../debugging.h"

using namespace std;
using GP = gp::GardenProtocol;
using SP = staticpath::_staticPath;
///////////////////////////////
//         constructor       //
///////////////////////////////

GardenTag::GardenTag(string treeHash, string msg, string parentsignature) {
  tag = alloc_tag(treeHash.c_str(), msg.c_str(), parentsignature.c_str());
  tagHashing(tag,&tag->tag_hash);
  if(!tag) 
      throw bad_alloc();
};
       
GardenTag::GardenTag(std::string hash) {

    std::ifstream in(SP::_TAGROOT(hash).string());
    if (!in) {
        throw std::runtime_error("GardenTag constructor Failed to open tag file");
    }
    string tagData[3];// 0: parent, 1: msg, 2: tree
    std::string line;
                                                                                    LOG("\n\nbefore while\n");
    while (std::getline(in, line)) {
        if(line.size()==0)break;

        vector<string> vec = GP::GardenDecode(line);

        if(vec.size()<2){
            throw runtime_error("invalid amount of data in GardenTag");
        }
        const std::string type = vec[0];
    
        if      (type == "[PARENT]") tagData[0] = vec[1];
        else if (type == "[MSG]")    tagData[1] = vec[1];
        else if (type == "[TREE]")   tagData[2] = vec[1];
        else throw std::runtime_error("Unrecognized tag in GardenTag");
    }    
    tag = alloc_tag(tagData[2].c_str(), tagData[0].c_str(), tagData[1].c_str());
}

///////////////////////////////
//      functionnality       //
///////////////////////////////

void GardenTag::write(){
    fs::path target = SP::_TAGROOT(getTagHash());

    if (fs::exists(target))
        throw runtime_error("tag path already exist");
    
    fs::create_directories(target.parent_path());
    std::ofstream outFile(target);
    
    outFile <<GP::GardenEncode({"[PARENT]", getParentHash()})<<"\n";
    outFile <<GP::GardenEncode({"[MSG]",    getMessage()})   <<"\n";
    outFile <<GP::GardenEncode({"[TREE]",   getRootHash()})  <<"\n";
    outFile.close();
}

GardenTag GardenTag::previousTag(GardenTag& tag){   
    GardenTag previous = GardenTag(tag.getParentHash());
    return previous;
}


///////////////////////////////
//      GETTER / SETTER      //
///////////////////////////////

string GardenTag::getTagHash() {
    return tag->tag_hash;
}
string GardenTag::getRootHash() {
    return tag->tree_hash;
}
string GardenTag::getParentHash() {
  return tag->parent_hash;
}
string GardenTag::getMessage() {
  return tag->message;
}
//no use for now
string GardenTag::getTimestamp() {
  return ctime(&tag->timestamp);
}
GardenTag_s *GardenTag::getStructValue() {
  return tag;
}


/////////////////////////////////////////////
///                PRIVATE                ///
/////////////////////////////////////////////



