#include "HashTree.h"

#include "../utilz/processes/Hashing.h"

#define LOGGER_STATUS LOGGER_INACTIVE
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
                                                                
        for(const auto &entry: fs::directory_iterator(parentNode->getPath())){
            // TODO:: make class for ignore
            if(entry.path().filename() ==".garden") { continue; } 

            if(fs::is_regular_file(entry)){
                                                                                
                FileNode *fileNode =  new FileNode(entry);
                
                parentNode->addfile(fileNode);
                                                                                                                        
            } else if(fs::is_directory(entry)) {
                                                                                                                    
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

    
    
