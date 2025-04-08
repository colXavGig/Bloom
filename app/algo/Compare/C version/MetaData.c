#include "MetaData.h"

/**
 * Line should look like  [File system object] [Hash] [filename+extension]
 * while read a line and create an object MetaDataFOS_S 
 * @param metadata ptr to struct to fill data
 * @param line takes a line in folder text
 */
int MetaDataFOS_init(MetaDataFOS_S* metadata, char* line){
    int i=0;
    while(line[i++] == ' ');//remove potential whitespace

    //assignation
    char *ptr=metadata->filetype;
    while(line[i]!=' '){
       *ptr++=line[i++];
    }
    *ptr = '\0';

    ptr = metadata->signature;
    while(line[i]!=' '){
        *ptr++=line[i++];
    }
    *ptr = '\0';

    ptr = metadata->filename;
    while(line[i]!=' '){
        *ptr++=line[i++];
    }
    *ptr = '\0';
}

/**
 * looks at data between two MetaDataFOS_S
 * if the type is WRONG it returns WRONGTYPE (3)
 * if name == and signature == SAME 0
 * if the name == and signature !=
 * if the name != either BIG 3 or SMALL 4
 * @param head 
 * @param dest 
 */
int MetaDataFOS_compare(const MetaDataFOS_S* head, const MetaDataFOS_S* dest){
    //check if file are the same type
    if(strcomp(head->filetype,dest->filetype)==0)return WRONGTYPE;

    int namediff = strcomp(head->filename,dest->filename);
    int signaturediff = strcomp(head->signature,dest->signature);
   
    if (namediff == 0 && signaturediff == 0) return SAME;
    if (namediff == 0 && signaturediff != 0) return DIFF;
    return (namediff > 0) ? BIG  : SMALL;
}
int MetaDataFOS_free(MetaDataFOS_S* metadata){
    metadata->filetype = NULL;
    metadata->signature = NULL;
    metadata->filename = NULL;
    free(metadata);
}