#include "datacollection/hashTree/HashTree.h"
#include "fileWriter/FileWriter.h"
#include "paths/GardenPath.h"
#include "fileReader/FileIterator.h"
#include "growth/Growth.h"
#include "index/Index.h"

#define LOGGER_STATUS LOGGER_ACTIVE
#include "debugging.h"


void commit(GardenPath *paths, char** arr, int size);

int main(int argc, char** argv){
    auto paths = GardenPath(".");
    LOG("Index created");
    LOG(".");
    LOG(".");
    LOG(".");
    LOG(".");
    LOG(".");
    LOG(".");
    LOG(".");
    LOG(".");
    printf(".");
    string cmd = (argc > 1) ? argv[1] :/* === DEFAULT === */ "commit";
    printf("here");
    LOG(("Command : " + cmd).c_str());
    auto index = Index(paths.getIndexFilepath());
    if (cmd == "commit") {
        commit(&paths, argv +2, argc -2);

    } else if (cmd == "comp"){


        FileIterator *it1 = new FileIterator("./app/testing/blob.txt");
        FileIterator *it2 = new FileIterator("./app/testing/blob2.txt");
        Growth g;
        while(it1->Next() | it2->Next()){
            g.compare(it1->getLine(),it1->getIndex(),it2->getLine(),it2->getIndex());
        }
        g.printChange();
    }

    // index.save();
    LOG("success");
    //getchar();
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
