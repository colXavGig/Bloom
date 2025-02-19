#pragma once

#include "Array_context.h"
#include "Flower.h"
#include "String.h"

struct trunkNode;

typedef union {
    struct trunkNode subtrunk;
    Flower flower;
} NodeData;

typedef struct trunkNode {
    NodeData data;
    String data_name;
    bool isFlower;
} TrunkNode;

typedef struct {
    Hash hash;
    TrunkNode *(*nodes)[];
    Array_ctx nodes_ctx;
} Trunk;

Trunk *get_trunk(String dir_path);
void free_trunk(Trunk *trunk);

