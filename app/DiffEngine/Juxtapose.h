#pragma once
#include "../FOS/FOS_metadata.h"
#include "Block.h"
#include "Diff.h"
#include "../paths/GardenPath.h"
#include <stdio.h>
#include <string>
#include<iostream>


#include "../fileSystemManagement/utilz/PathManagement/StaticPath.h"
using SP = staticpath::_staticPath;
/**
 * class pour comparer deux FileTrees dans le garden
 * il lit le folder file dependament du resultat il enregistre des donne
 */
class Juxtapose{
    private:
        std::vector<Block> parentBlocks;
        std::vector<Block> headBlocks;
        //diff list
        Diff root;
    //------------------ helper functions ------------------//

        void loadBlocks(const char* signature, std::vector<Block>& blockList);
    public:   
        void parseMetadata(const std::string& sign1, const std::string& sign2, std::string path);
        void compareBlocks();

        Diff getroot(){ return root; }
        void readroot(){ root.readAll(); }
};




