#include "GardenTag_struct.h"




#define ERR_BAD_ALLOC 2
#define ERR_NULL_PTR 3
#define ERR_NONEXISTANTE_VALUE 4
#define ERR_INVALID_OPERATION 5



int set_message_tag(GardenTag_s *tag, const char *msg){
    tag->message = strdup(msg);
    if(!tag->message) return ERR_BAD_ALLOC; 
    return 1;
}



GardenTag_s *alloc_tag(const char *tree_hash, const char *parent_hash){
    if(!tree_hash || !parent_hash) return NULL;

    GardenTag_s *tag = malloc(sizeof(GardenTag_s));
    if (!tag) return NULL;
   
    strncpy(tag->tree_hash, tree_hash, HASH_STR_SIZE);
    tag->tree_hash[HASH_STR_SIZE-1] = '\0';

    strncpy(tag->parent_hash, parent_hash, HASH_STR_SIZE);
    tag->parent_hash[HASH_STR_SIZE-1] = '\0';

    int e3 = set_message_tag(tag, "[NONE]");

    if(e3 != 1){
        free(tag->message);
        free(tag);
        return NULL;       
    } 

    tag->timestamp = time(NULL);

    return tag;
}

void free_tag(GardenTag_s *tag){
    free(tag->message);
    free(tag);
}

//setters for builder

