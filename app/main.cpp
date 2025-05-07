#include "fileSystemManagement/seed/HashTree.h"
#include "fileSystemWriter/FileWriter.h"

#include "fileSystemBuilder/fileBuilder.h"
//#include "algo/Juxtapose.h"
#include <iostream>

#define LOGGER_STATUS LOGGER_ACTIVE
#include "debugging.h"
#include <string>

//path management
#include "paths/GardenPath.h"
#include "fileSystemManagement/utilz/GardenProtocol/GardenProtocol.h"
#include "fileSystemManagement/utilz/PathManagement/StaticPath.h"
using SP = staticpath::_staticPath;

#include "DiffEngine/TreeDiff.h"
int main(int argc, char** argv){

    SP::SET(std::make_unique<GardenPath>("."));
    Index index = Index();

    string cmd = (argc > 1) ? argv[1] :/* === DEFAULT === */ "commit";
                                                                                                                        LOG(("Command : " + cmd).c_str());
    /////////////////////////////
    //       init / save       //
    /////////////////////////////
    //major actions
    if (cmd == "init") {// commit and update necessary component
        HashTree hashT = HashTree(new FolderNode("./app/testing"));//for testing
        fileWriter fw;
        fw.init(&hashT,"INIT",&index);
    }
    else if (cmd == "commit") {// commit and update necessary component
        try{
            index.read();
            //TODO:: handle les exceptions
            HashTree hashT = HashTree(new FolderNode("./app/testing"));//for testing

            fileWriter fw;
            fw.commit(&hashT, argv[2],&index);

        } catch(const ios_base::failure& e){
            cerr<<"Index not found pls init... ";
        }
    }

    ///////////////////////////////
    //          branche          //
    ///////////////////////////////
    else if (cmd == "plant"){//create new branch
        index.read();
        index.plant(argv[2]);
    }
    else if (cmd == "check"){ //switch new branch
        index.read();
        index.setCurrent(argv[2]);
        FileBuilder *fb = new FileBuilder();
        fb->reset();//reset filesystem
        try{

            GardenTag tag = GardenTag(index.getTagHash());

            fb->build(tag.getRootHash());
        } catch(const runtime_error &e){
            cerr<< e.what();
        }
    }    
    else if(cmd == "index"){// index additionnal functionnality
        std::string subcmd = argv[2];
        if (subcmd == "ls") {
            index.read();
            index.ls();
        }
        else {
            //TODO:: rajouter distance de leveinschteine afin de trouver quelle commande est plus familiere
            throw runtime_error("bad commande");
        }
    }

    else if (cmd == "diff") {
        try{
            index.read();
            string headHash = "58b988d90e305b49b77858973feada6fe72a298f";    
            string targetHash = "429e9e9ed1dbbf0a1342c420fdfe2393ab08accd";  

            TreeDiff diffEngine;
            diffEngine.compareTrees(headHash, targetHash);

            Diff& result = diffEngine.getDiff();

            if (result.hasConflicts()) {
                cout << "Merge conflicts detected!\n";
            } else {
                cout << "No conflicts.\n";
            }
            result.readAll(); 
        } catch (const std::exception& e) {
            cerr << "Fatal error: " << e.what() << std::endl;
        }
    }
    else if (cmd == "merge") {
        index.read();
        //find commun commit
        
    }
    else if (cmd == "revert") {
        index.read();
    }

    //////////////////////////////
    //          Garden          //
    //////////////////////////////    
    else if (cmd == "push") {
        index.read();
    }
    else if (cmd == "pull") {
        index.read();
    }
    //////////////////////////////
    //          tags            //
    //////////////////////////////  
    //gardenTag additionnal functionnality
    else if(cmd == "tag"){
        std::string subcmd = argv[2];
        if (cmd == "ls") {
            index.read();
        }
    }
    
    LOG("before save");
    index.save();
    LOG("success");
}


