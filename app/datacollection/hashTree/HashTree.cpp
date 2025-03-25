#include "HashTree.h"
    /*
    Constructeur prends une directory
    et copy le filesystem a partir.
    */
    HashTree::HashTree(FolderNode *r):root(r) {
        createTree(root);  
    }

    /*
    fonction Recursive, creer le tree et set les information importantes
    pour faire la sauvegarde. 
    */
    void HashTree::createTree(FolderNode *parentNode){
        
        cout<<"creating a folder: "<<parentNode->getFileName()<<"\n";

        for(const auto &entry: fs::directory_iterator(parentNode->getPath())){
            if(fs::is_regular_file(entry)){
                FileNode *fileNode =  new FileNode(entry);
                cout<<"creating a file: "<<fileNode->getFileName()<<"\n";
                parentNode->addfile(fileNode);
            } 
            else if(fs::is_directory(entry)){
                FolderNode *folderNode =  new FolderNode(entry);
                createTree(folderNode);
                parentNode->addfolder(folderNode); 
            }  
        }
        parentNode->setSignature();
    }
 
    // void HashTree::listBranches(HashNode* node, int depth){
    //     return;
    // }
    
