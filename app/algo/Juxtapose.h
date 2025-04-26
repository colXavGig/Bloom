#pragma once

#include "Stack/FunctionStack.h"
#include "FOS/MetaData.h"
#include "FOS/FILE_S.h"
#include "diff.h"
#include "../paths/GardenPath.h"
#include "FOS/FOS_MD_QUEUE.cpp"
#include <stdio.h>
#include <string>

/**
 * class pour comparer deux FileTrees dans le garden
 * il lit le folder file dependament du resultat il enregistre des donne
 */
class Juxtapose{
    private:
        GardenPath path= GardenPath(".");
        FOS_MD_QUEUE parentQueue;
        FOS_MD_QUEUE headQueue;
        //diff list
        Diff root;
    //------------------ helper functions ------------------//

        void parsefolder (std::string path);
        void parsefile   (std::string path);
        void fillqueues(FOS_MD_QUEUE& fos, const char *sign1);
    public:   

    void parseMetadata(const char *sign1, const char *sign2, std::string path);
    void compare(const char *sign1, const char *sign2,const char *type,const char *filename, std::string p);
    
};




