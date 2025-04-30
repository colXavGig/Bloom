#include "datacollection/hashTree/HashTree.h"
#include "fileSystemWriter/FileWriter.h"
#include "paths/GardenPath.h"
#include "fileSystemBuilder/fileBuilder.h"
//#include "algo/Juxtapose.h"
#include <iostream>
#include "index/Index.h"
#define LOGGER_STATUS LOGGER_INACTIVE
#include "debugging.h"

void commit(Index& index, GardenPath *paths, char** arr, int size);

int main(int argc, char** argv){
    GardenPath paths = GardenPath(".");
    Index index = Index(paths.getIndexFilepath());

    string cmd = (argc > 1) ? argv[1] :/* === DEFAULT === */ "commit";
    LOG(("Command : " + cmd).c_str());
    if (cmd == "commit") {
       commit(index, &paths, argv +2, argc -2);

    } 
    else if (cmd == "comp"){

    //     Juxtapose diff;
    //     try{
    //         diff.parseMetadata("0a5c758ae3608bd5a2a3a8750409256cbc5e2ff2.txt",
    //                            "80c0b919e881434f1e18fc097bc79033014e31eb.txt","myLOOOOOOVE");
    //     } catch(const runtime_error &err){
    //        cerr<< err.what();
    //     }
    //     diff.readroot();
    // cout<<"succes";
    }
    else if (cmd == "plant"){

        index.createNewBranch(argv[2],index.getHash());
        LOG("here")
    }
    else if (cmd == "check"){
        index.changeBranch(argv[2]);

        FileBuilder *fb = new FileBuilder(&paths);
        fb->reset();
        try{

            fs::path p = paths.getGardenTagPath(index.getHash());
            cout << p<<"\n";
            GardenTag tag = GardenTag(p) ;
            fb->build(tag.getHash());

        } catch(const runtime_error &err){
            cerr<< err.what();
        }
    }

    index.save();
    LOG("success");
}

void commit(Index& index, GardenPath *paths, char** arr, int size) {
    string tag_msg = (arr[0] == "-m") ? arr[1] : "<EMPTY>";
    LOG(("Tag message: \"" + tag_msg + "\"!").c_str());

    FolderNode *root = new FolderNode("./app/testing");
    LOG("FolderNode created!");

    HashTree HTree =  HashTree(root);
    LOG("HashTree created!");
    fileWriter fw = fileWriter(paths);
    LOG("FileWriter created!");

    index.commit(fw.writeToFile(&HTree, tag_msg,index.getHash()));
    LOG("HashTree written!");
}
