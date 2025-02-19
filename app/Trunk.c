#include "Trunk.h"

Trunk *get_trunk(String dir_path) {

}

Trunk *new_Trunk() {
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