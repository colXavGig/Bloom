#pragma once
#include <vector>
#include "../FOS/FOS_metadata.h"
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <queue>

class FOS_MD_QUEUE{
    public:
        std::queue<MetaDataFOS_S> folderQueue;
        std::queue<MetaDataFOS_S> fileQueue;

    void addToQueue(const MetaDataFOS_S& fos){
        if(strcmp(fos.fostype, "[FOLDER]") == 0) folderQueue.push(fos);
        else if(strcmp(fos.fostype, "[FILE]") == 0)fileQueue.push(fos);
    }
};