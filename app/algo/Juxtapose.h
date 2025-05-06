#pragma once
#include "../FOS/FOS_metadata.h"
#include "Block.h"
#include "diff.h"
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
        void parseMetadata(const char *sign1, const char *sign2, std::string path);
        void compareBlocks();

        Diff getroot(){ return root; }
        void readroot(){ root.readAll(); }
};




