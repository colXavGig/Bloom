#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

#include "GardenTag_struct.h"
#include "../seed/HashTree.h"
#include "../utilz/GardenProtocol/GardenProtocol.h"
#include "../utilz/PathManagement/StaticPath.h"


using namespace std;
namespace  fs =  std::filesystem;

/**
 * class that holds the data to point to a commit of an Hashtree
 */
class GardenTag{
    public:
        /**
        * Construct a GardenTag with the specified root
        * @param tree the tree that the tag should point to
        * @param msg the message recorded by the user to explain the changed in the repo
        * @param parentsignature signature du tag precedent
        */
        GardenTag(string treeHash, string msg, string parentsignature);
        /**
        * constructor for the garden
        * @param hash hash of the tag
        */
        GardenTag(std::string hash);
    
        GardenTag(GardenTag_s *value) {
            this->tag = value;
        }

        GardenTag(nlohmann::json data);

        string getTagHash();
        string getRootHash();
        HashTree* getRoot(); // needed for toJson()
        string getParentHash();
        string getMessage();
        string getTimestamp();     
        GardenTag_s *getStructValue();
        
        
        ///////////////////////////
        //     functionnality    //
        ///////////////////////////
        
        void write();

        nlohmann::json toJson();
        nlohmann::json toJsonToSignature(std::string signature);

        static GardenTag fromJson(nlohmann::json data);

        GardenTag previousTag(); // NOTE: Doesnt need a reference to a tag, it can use the this keyword

        operator GardenTag_s *() {
            return tag;
        }    
    private:
        GardenTag_s *tag;

        void setMessage(string message); 

};