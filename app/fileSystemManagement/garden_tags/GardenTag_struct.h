#pragma once
#define HASH_SIZE 20
#define HASH_STR_SIZE (HASH_SIZE * 2 + 1)
#include <time.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
    char tree_hash[HASH_STR_SIZE];
    char parent_hash[HASH_STR_SIZE];
    char *message;
    time_t timestamp; 
    
    char tag_hash[HASH_STR_SIZE];
} GardenTag_s;

GardenTag_s *alloc_tag(const char *root_hash, const char *parentHash, const char *msg);
void free_Tag(GardenTag_s *garden);

int set_message(GardenTag_s *tag, const char *msg);

#ifdef __cplusplus
}
#endif