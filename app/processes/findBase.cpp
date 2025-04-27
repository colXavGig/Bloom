#include "stdio.h"
#include "../garden_tags/GardenTag_struct.h"
#include "../index/Index.h"
#include "../paths/GardenPath.h"


void GardenToMemory(const char* signature, GardenTag_s* memory){
    std::string p =GardenPath::signaturePath(signature);

    

}


GardenTag_s* findBase(Index_s*current, Index_s *index){
    //trouver le dernier commit



}


