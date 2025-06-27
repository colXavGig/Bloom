#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "../../utils/path/StaticPath.h"
#include "c/GardenTag_struct.h"

using namespace std;
/**
 * class that holds the data to point to a commit of an Hashtree
 * takes a hash tree 
 */
class GardenTag{
    public:

        GardenTag(GardenTag_s *value) {
            this->tag = value;
        }

        GardenTag(string tree_hash,string parent_tag_hash);

        GardenTag_s set_message(string message);         
  

        string get_tag_hash();
        string get_root_hash();
        string get_parent_hash();
        string get_message();
        string get_time_stamp();     
        GardenTag_s *get_struct_value();

        ///////////////////////////
        //     functionnality    //
        ///////////////////////////

        void write();
        operator GardenTag_s *() {
            return tag;
        }    
    private:
        GardenTag_s *tag;
};
