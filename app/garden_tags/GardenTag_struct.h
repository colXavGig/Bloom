#pragma once

#include <time.h>

#include "../datacollection/hashTree/HashNode_struct.h"

// tell cpp compiler to compile in C
#ifdef __cplusplus
extern "C" {
#endif

typedef struct GardenTag_s {
    char *message;
    char *signature;
    time_t timestamp;
    HashNode_s *root;
} GardenTag_s;

#ifdef __cplusplus
}
#endif