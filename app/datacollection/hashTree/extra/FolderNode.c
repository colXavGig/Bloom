#include "FolderNode.h"

void foldernode_init(FolderNode *node, const char *path, const char *filename ){
    genericvector_init(node->file,0);
    genericvector_init(node->folder,0);

    node->path=strdup(path);
    node->path=strdup(filename);
}

void getHash(FolderNode *node){
    //initialisation du vector qui prends le hash
    StringVector *vec;
    stringvector_init(&vec);
    
    int i;
    if(node->file != NULL){
        i=0;
        FileNode *file=NULL;
        while(get(node->file,i++,(void**)&file)==1){
           push_back(vec,(unsigned char*)file->hash);
        }
    }

    if(node->folder != NULL){
        i=0;
        FolderNode *folder=NULL;
        while(get(node->folder,i++,(void**)&folder)==1){
           push_back(vec,(unsigned char*)folder->hash);
        }
    }
    
}