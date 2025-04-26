#include "datacollection/hashTree/HashTree.h"
#include "fileWriter/FileWriter.h"
#include "paths/GardenPath.h"

#include "algo/Juxtapose.h"
#include <iostream>

#define LOGGER_STATUS LOGGER_INACTIVE
#include "debugging.h"

void commit(GardenPath *paths, char** arr, int size);

int main(int argc, char** argv){
    GardenPath paths = GardenPath(".");
    string cmd = (argc > 1) ? argv[1] :/* === DEFAULT === */ "commit";
    LOG(("Command : " + cmd).c_str());
    if (cmd == "commit") {
        commit(&paths, argv +2, argc -2);


    } else if (cmd == "comp"){

        Juxtapose diff;
        try{
            diff.parseMetadata("0a5c758ae3608bd5a2a3a8750409256cbc5e2ff2.txt",
                               "0a5c758ae3608bd5a2a3a8750409256cbc5e2ff2.txt","myLOOOOOOVE");
        } catch(const runtime_error &err){
           cerr<< err.what();
        }
        
    cout<<"succes";
    } else if (cmd == "growback"){
     
    cout<<"succes";


    }


    LOG("success");
}

void commit(GardenPath *paths, char** arr, int size) {
    string tag_msg = (arr[0] == "-m") ? arr[1] : "<EMPTY>";
    LOG(("Tag message: \"" + tag_msg + "\"!").c_str());

    FolderNode *root = new FolderNode("./app/testing");
    LOG("FolderNode created!");

    HashTree HTree =  HashTree(root);
    LOG("HashTree created!");

    fileWriter fw = fileWriter(paths);
    LOG("FileWriter created!");

    fw.writeToFile(&HTree, tag_msg);
    LOG("HashTree written!");
}
