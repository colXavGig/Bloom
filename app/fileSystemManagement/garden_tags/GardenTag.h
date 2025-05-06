#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "GardenTag_struct.h"
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

        string getTagHash();
        string getRootHash();
        string getParentHash();
        string getMessage();
        string getTimestamp();     
        GardenTag_s *getStructValue();

        ///////////////////////////
        //     functionnality    //
        ///////////////////////////

        void write();

        GardenTag previousTag(GardenTag& tag);

        operator GardenTag_s *() {
            return tag;
        }    
    private:
        GardenTag_s *tag;

        void setMessage(string message); 

};