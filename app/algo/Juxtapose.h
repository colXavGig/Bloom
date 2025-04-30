#pragma once
#include "../FOS/FOS_metadata.h"
#include "FOS/FILE_S.h"
#include "diff.h"
#include "../paths/GardenPath.h"
#include "FOS_MD_QUEUE.cpp"
#include <stdio.h>
#include <string>
#include<iostream>
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
    void compareSingleValidFile(MetaDataFOS_S* md, bool isParent, std::string p);
    void compareBothValidFiles(MetaDataFOS_S* pmd, MetaDataFOS_S* cmd, std::string p);


    void readroot(){
        root.readAll();
    }
};




