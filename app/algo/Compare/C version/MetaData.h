#include <stdio.h>
#include <stdlib.h>
#define SAME 0
#define DIFF 1
#define WRONGTYPE 2
#define BIG 3
#define SMALL 4


/**
 * Structure qui represent un filesystem object en c
 * 
 * @param filetype type soit folder ou file
 * @param signature le hash de la fonction
 * @param filename le nom + extension de la fonction
 */
typedef struct {
    char *filetype;
    char *signature;
    char *filename; 
}MetaDataFOS_S;

int MetaDataFOS_init(MetaDataFOS_S*,char*);
int MetaDataFOS_compare(const MetaDataFOS_S* , const MetaDataFOS_S*);
void MetaDataFOS_free(const MetaDataFOS_S* head);