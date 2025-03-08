#include "Trunk.h"
#include "PathList.c"
#include "filesys_utils.c"

int get_trunk_hash(Path dir_path, Hash *out) {
    Trunk *trunk = newTrunk();
    if (trunk ==NULL) {
        puts("could not generate tunk");
        return NULL;
    }

    PathList *pathList = newPathList(10);
    get_dir_content(dir_path.name.value, pathList);
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    for (int i = 0; i < pathList->ctx.length; i++) {
        Path p = (*pathList->paths)[i];
        if (strcmp(p.type.value, "dir") == 0) {
            Hash h;
            (void)get_trunk_hash(p, &h);
            SHA1_Update(&ctx, &h, sizeof h);
        } else if (strcmp(p.name.value, "file") == 0) {
            //Hash h = get
        }
        
    }
    
    SHA1_Final(out, &ctx);
    return 0;
    

}

Trunk *newTrunk() {
    Trunk *trunk = (Trunk *)malloc(sizeof(trunk));
    if (trunk == NULL) {
        printf("Could not allocate memory for trunk");
        return NULL;
    }

    trunk->nodes = (TrunkNode *(*)[])malloc(sizeof(TrunkNode[8]));
    if (trunk->nodes == NULL) {
        free(trunk);
        printf("Could not allocate memory for tunk nodes");
        return NULL;
    }
    trunk->nodes_ctx.length = 0;
    trunk->nodes_ctx.capacity = 8;

    return trunk;

}

TrunkNode *new_TrunkNode(String name) {
    TrunkNode *node = (TrunkNode *)malloc(sizeof(TrunkNode));
    if (node == NULL) {
        printf("Could not allocate memory for trunkNode");
        return NULL;
    }
    node->data_name = name;
    return node;
}

void free_trunk(Trunk *trunk) {
    
}