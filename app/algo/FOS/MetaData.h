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

static inline MetaDataFOS_S MetaDataFOS_S_Invalid() {
    MetaDataFOS_S metadata;
    metadata.fostype = NULL;
    metadata.signature = NULL;
    metadata.fosname = NULL;
    return metadata;
}
#endif