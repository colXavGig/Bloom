#include "GardenTag.h"
#include "c/GardenTag_struct.h"



#define LOGGER_STATUS LOGGER_INACTIVE
#include "../../debugging.h"

using namespace std;
using SP = staticpath::_staticPath;
///////////////////////////////
//         constructor       //
///////////////////////////////

GardenTag::GardenTag(string tree_hash, string parent_tag_hash) {
 tag = alloc_tag(tree_hash.c_str(),parent_tag_hash.c_str());
}


GardenTag_s GardenTag::set_message(string message){
  free(tag->message);
  set_message_tag(tag, message.c_str());
}


///////////////////////////////
//      functionnality       //
///////////////////////////////

void GardenTag::write(){
    fs::path target = SP::_TAGROOT(get_tag_hash());
    if (fs::exists(target))
        throw runtime_error("tag path already exist");
    
    fs::create_directories(target.parent_path());
    std::ofstream outFile(target);
    
    outFile <<GP::GardenEncode({get_parent_hash()+" "+
                                get_root_hash()  +" "+
                                get_message()    +"\n"})    
    outFile.close();
}

GardenTag GardenTag::previousTag(GardenTag& tag){   
    GardenTag previous = GardenTag(tag.get_parent_hash());
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



