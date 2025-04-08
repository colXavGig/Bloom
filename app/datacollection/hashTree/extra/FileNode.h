#include "stdio.h"
#include "stdlib.h"
#include "../../processes/Hashing.h"

typedef struct{
    char *hash;
    char *fileName;
    char *path;   
} FileNode;

void filenode_init(FileNode *node, const char *path, const char *filename );
