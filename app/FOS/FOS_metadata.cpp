#include "FOS_metadata.h"
#include <iostream>
using namespace std;
using GP = gp::GardenProtocol;
//--------------------------------//
//          constructor           //
//--------------------------------//

/**
 * null data type;
 */
FOS_metadata::FOS_metadata(){
    metadata = new metadataFOS_S;
    metadata->fostype = nullptr;
    metadata->fosname = nullptr;
    metadata->hash[0] = '\0';
}

/**
 * Line should look like  [File system object] [Hash] [filename+extension]
 * while read a line and create an object MetaDataFOS_S 
 * @param line takes a line in folder text
 */
FOS_metadata::FOS_metadata(const std::string& line){
    metadata = new metadataFOS_S;
    metadata->fostype = nullptr;
    metadata->fosname = nullptr;

    vector<string> data = GP::GardenDecode(line);
    if (data.size() < 3) {
        throw std::runtime_error("FOS_metadata::FOS_metadata - make de data corruption de memoire a la lecture");
    }

    setType(data[0]);

    setHash(data[1]);

    setName(data[2]);

}


FOS_metadata::~FOS_metadata(){
    if (metadata) {
        delete[] metadata->fostype;
        delete[] metadata->fostype;
        delete metadata; 
        metadata = nullptr;
      }
}
//--------------------------------//
//        setter / getter         //
//--------------------------------//

void FOS_metadata::setType(std::string type){ 
    if (!metadata) {
        std::cerr << "ERROR: metadata is null in setType!\n";
        return;
    }
    delete[] metadata->fostype;  
    metadata->fostype = new char[type.size() + 1];
    std::strcpy(metadata->fostype, type.c_str());
}

void FOS_metadata::setHash(std::string hash){

    strncpy(metadata->hash, hash.c_str(), sizeof(metadata->hash) - 1);
    metadata->hash[sizeof(metadata->hash) - 1] ='\0';
}

void FOS_metadata::setName(std::string name){
    if (!metadata) {
        std::cerr << "ERROR: metadata is null in setName!\n";
        return;
    }
    delete[] metadata->fosname;  
    metadata->fosname = new char[name.size() + 1];
    std::strcpy(metadata->fosname, name.c_str());
}

std::string FOS_metadata::getHash(){
    return std::string(metadata->hash);
}
std::string FOS_metadata::getType(){
    return std::string(metadata->fostype);
}
std::string FOS_metadata::getName(){
    return std::string(metadata->fosname);
}
metadataFOS_S *FOS_metadata::getStructuralValue(){
    return metadata;
};


//--------------------------------//
//           comparator           //
//--------------------------------//
/**
 * check if metadata is null
 * @return if metadata is default constructed with out setting anything it will return false
 */
bool FOS_metadata::isEmpty(){
    return (metadata->fostype   == nullptr && 
            metadata->hash[0]   == '\0' &&
            metadata->fosname   == nullptr);   
}
bool FOS_metadata::diffHash(const FOS_metadata& md){
    return strcmp(metadata->hash, md.metadata->hash);
}
bool FOS_metadata::difftype(const FOS_metadata& md){
    return strcmp(metadata->fostype, md.metadata->fostype);
}
int  FOS_metadata::diffName(const FOS_metadata&md){
    return strcmp(metadata->fosname, md.metadata->fosname);
}

