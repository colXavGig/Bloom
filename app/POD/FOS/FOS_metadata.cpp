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
    

    vector<string> data = GP::GardenDecode(line);
    if (data.size() < 3) {
        throw std::runtime_error("FOS_metadata::FOS_metadata - make de data corruption de memoire a la lecture");
    }
    char hash_arr[41];
    strncpy(hash_arr, data[1].c_str(), 41);
    hash_arr[40] = '\0';

    metadata = metadata_init(data[0].c_str(),&hash_arr,data[2].c_str());

}


FOS_metadata::~FOS_metadata(){
    metadata_free(metadata);
}
//--------------------------------//
//        setter / getter         //
//--------------------------------//

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
bool FOS_metadata::isHashEqual(const FOS_metadata& md){
    return strcmp(metadata->hash, md.metadata->hash);
}
bool FOS_metadata::isTypeEqual(const FOS_metadata& md){
    return strcmp(metadata->fostype, md.metadata->fostype);
}
int  FOS_metadata::isNameEqual(const FOS_metadata&md){
    return strcmp(metadata->fosname, md.metadata->fosname);
}

