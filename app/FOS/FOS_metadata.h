#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include "stdexcept"

#include "FOS_metadata_struct.cpp"
#include "../fileSystemManagement/utilz/GardenProtocol/GardenProtocol.h"
/**
 * une classe qui represente un FOS
 */
class FOS_metadata {
    public:
        //default constructor is nullstate;
        FOS_metadata();
        //constructeur du gardent
        FOS_metadata(const std::string& line);
        //constructeur du fileSytem
        FOS_metadata(char *fostype, char *signature, char *fosname);
        ~FOS_metadata();
        
        //SETTER
        void setHash(std::string hash);
        void setType(std::string type);
        void setName(std::string name);
        //GETTER
        std::string getHash();
        std::string getType();
        std::string getName();
        metadataFOS_S *getStructuralValue();

        //boolean
        bool isEmpty();
        bool diffHash(const FOS_metadata& hash);
        bool difftype(const FOS_metadata& type);
        int  diffName(const FOS_metadata& type);

        //formating / print state
        std::string toString();

        //OPERATOR OVERLOADING
        bool operator==(const FOS_metadata& other) {
            return (strcmp(metadata->fostype, other.metadata->fostype)==0)    
            && (strcmp(metadata->fosname, other.metadata->fosname)==0) 
            && (strcmp(metadata->hash, other.metadata->hash)==0); 
        }

        bool operator!=(const FOS_metadata& other) {
            return !diffHash(other);    
        }

        private:   
        metadataFOS_S *metadata;

};


