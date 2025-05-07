#pragma once
#include<string.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Structure qui represent un filesystem object en c
 * 
 * @param fostype type soit folder ou file
 * @param signature le hash de la fonction
 * @param fosname le nom + extension de la fonction
 */
typedef struct {
    char *fostype;
    char  hash[41];
    char *fosname; 
}metadataFOS_S;


#ifdef __cplusplus
}
#endif



