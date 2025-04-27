#ifndef METADATA_H
#define METADATA_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Structure qui represent un filesystem object en c
 * 
 * @param fostype type soit folder ou file
 * @param signature le hash de la fonction
 * @param fosname le nom + extension de la fonction
 */
typedef struct {
    char *fostype;
    char *signature;
    char *fosname; 
}MetaDataFOS_S;

MetaDataFOS_S MetaDataFOS_init(char*);
void MetaDataFOS_free( MetaDataFOS_S* md);
void MetaDataFOS_text(MetaDataFOS_S* md);

//NULL State
static inline MetaDataFOS_S MetaDataFOS_S_NULLSTATE() {
    MetaDataFOS_S metadata;
    metadata.fostype   = nullptr;
    metadata.signature = nullptr;
    metadata.fosname   = nullptr;
    return metadata;
}

static inline bool MetaDataFOS_S_isEmpty(const MetaDataFOS_S* md) {
    return (md == nullptr) ||
    (md->fostype == nullptr && md->signature == nullptr && md->fosname == nullptr);
}

static inline int safe_strcmp(const char* a, const char* b) {
    if (a == nullptr && b == nullptr) return 0;
    if (a == nullptr) return -1;
    if (b == nullptr) return 1;
    return strcmp(a, b);
}

#endif