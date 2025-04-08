#include "FileNode.h"

void filenode_init(FileNode *node, const char *path, const char *filename ){
    char buffer[HASH_SIZE];
    fileHash(path,buffer);
    node->hash = buffer;
    node->path = strdup(path);
    node->fileName = strdup(filename);
};
