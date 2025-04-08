#include "stdio.h"
#include "stdlib.h"
#include "../dynamicarray/Vector.h"
#include "GenericVector.h"
#include "FileNode.h"

typedef struct{
    char *hash;
    char *fileName;
    char *path;
    GenericVector *file;
    GenericVector *folder;
} FolderNode;

void foldernode_init(FolderNode *node, const char *path, const char *filename );

void getHash(FolderNode *node);