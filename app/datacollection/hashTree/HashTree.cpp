#include "HashTree.h"

#include "../../processes/Hashing.h"

#define LOGGER_STATUS LOGGER_ACTIVE
#include "../../debugging.h"
    /*
    Constructeur prends une directory
    et copy le filesystem a partir.
    */
    HashTree::HashTree(FolderNode *r){
        root = r;
        createProjectTree(getRoot());
    }

    // HashTree::HashTree(GardenTags *tag):root(tag->getRoot()) {
    //     createGardenTree(root);
    // }
    
    /*
    fonction Recursive, creer le tree et set les information importantes
    pour faire la sauvegarde. 
    */
    void HashTree::createProjectTree(FolderNode *parentNode){
                                                                                                                        LOG("");
                                                                                                                        LOG(("Creating a folder: " + parentNode->getFileName()).c_str());
                                                                                                                        LOG(("Path: " + parentNode->getPath().string()).c_str());
        for(const auto &entry: fs::directory_iterator(parentNode->getPath())){
                                                                                                                        LOG(("Entry: " + entry.path().string()).c_str());
            if(entry.path().filename() ==".garden") { continue; } // faut creer une classe ignore pour ignorer certain folder

            if(fs::is_regular_file(entry)){
                                                                                                                        LOG("");
                FileNode *fileNode =  new FileNode(entry);

                LOG(("Generated signature: " + fileNode->getSignature() ).c_str());
                
                parentNode->addfile(fileNode);
                                                                                                                        LOG("");
            } else if(fs::is_directory(entry)) {
                                                                                                                        LOG("File asigned as parent node...");
                FolderNode *folderNode =  new FolderNode(entry);
                createProjectTree(folderNode);
                parentNode->addfolder(folderNode);
            }  
        }
        LOG(("Created a folder: " + parentNode->getPath().string()).c_str());
        parentNode->generateSignature();
        LOG(("Generated signature: " + parentNode->getSignature()).c_str());
    }






    void HashTree::listBranches(FolderNode* parent){
        for(FileNode* file: parent->getFiles()){
            cout<<file->getPath()<<"\n";               
        }
        for(FolderNode* folder: parent->getFolders()){
            listBranches(folder);              
        }
    }

    
    
