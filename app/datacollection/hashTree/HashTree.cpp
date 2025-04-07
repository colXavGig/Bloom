#include "HashTree.h"

#include "../../processes/Hashing.h"
    /*
    Constructeur prends une directory
    et copy le filesystem a partir.
    */
    HashTree::HashTree(FolderNode *r):root(r) {
        createProjectTree(root);  
    }

    // HashTree::HashTree(GardenTags *tag):root(tag->getRoot()) {
    //     createGardenTree(root);
    // }
    
    /*
    fonction Recursive, creer le tree et set les information importantes
    pour faire la sauvegarde. 
    */
    void HashTree::createProjectTree(FolderNode *parentNode){
        
        cout<<"creating a folder: "<<parentNode->getFileName()<<"\n";

        for(const auto &entry: fs::directory_iterator(parentNode->getPath())){
            if(entry.path().filename() ==".garden"){continue;}// faut creer une classe ignore pour ignorer certain folder

            if(fs::is_regular_file(entry)){
                FileNode *fileNode =  new FileNode(entry);
                cout<<"creating a file: "<<fileNode->getFileName()<<"\n";
                parentNode->addfile(fileNode);
            } 
            else if(fs::is_directory(entry)){                
                    FolderNode *folderNode =  new FolderNode(entry);
                    createProjectTree(folderNode);
                    parentNode->addfolder(folderNode); 
            }  
        }
        parentNode->setSignature();
    }

     /*
    permet de recreer un HashTree a partir du .garden pas concret mais experimental
    */
    void HashTree::createGardenTree(FolderNode *parentNode){



    }



    void HashTree::listBranches(FolderNode* parent){
        for(FileNode* file: parent->getFiles()){
            cout<<file->getPath()<<"\n";               
        }
        for(FolderNode* folder: parent->getFolders()){
            listBranches(folder);              
        }
    }

    
    
