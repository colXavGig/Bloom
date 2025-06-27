#pragma once
#include "string.h"
#include "stdlib.h"
#define HASH_SIZE 20
#define HASH_STR_SIZE (HASH_SIZE * 2 + 1)
#include <time.h>
#ifdef __cplusplus
extern "C" {
#endif


typedef struct{
    char tag_hash[HASH_STR_SIZE];
    char tree_hash[HASH_STR_SIZE];
    char parent_hash[HASH_STR_SIZE];
    char *message;
    time_t timestamp; 
} GardenTag_s;

GardenTag_s *alloc_tag(const char *root_hash, const char *parentHash);
void free_tag(GardenTag_s *garden);

int set_message_tag(GardenTag_s *tag, const char *msg);

#ifdef __cplusplus
}
#endif
