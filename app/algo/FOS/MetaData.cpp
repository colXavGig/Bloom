#include "MetaData.h"

/**
 * Prends une ligne du .garden folderfiles 
 * et retourne chaque est char* separer par des ' ' 
 * 
 * @param line ligne d'un fichier 
 * @return a token (char *)
 */
char *charTokenMalloc(char **line){
    //whitespace
    while (**line == ' ') {
        (*line)++;
    }

    int size = 0;
    char *ptr = *line;
    //trouver la taille du token
    while(**line != ' ' && **line != '\n' && **line != '\0' && **line != EOF){
        size++;
        (*line)++;
    }
    //malloc la taille
    char *metadata = (char*)malloc(size+1);
    if(size==0){
        metadata[0] = '\0';
        return metadata;
    }
    
    char *mallocptr= metadata;

    while(*ptr != ' ' && *ptr != '\0'){
       *mallocptr++ = *ptr++;
    }
    *mallocptr = '\0';

    return metadata;   
}
/**
 * Line should look like  [File system object] [Hash] [filename+extension]
 * while read a line and create an object MetaDataFOS_S 
 * @param metadata ptr to struct to fill data
 * @param line takes a line in folder text
 * @return returns metadataFOS 
 */
MetaDataFOS_S MetaDataFOS_init(char* line){
    MetaDataFOS_S metadata ={0};

    metadata.fostype=charTokenMalloc(&line);
    metadata.signature=charTokenMalloc(&line);
    metadata.fosname=charTokenMalloc(&line);

    return metadata;
}

/**
 * console print metadataFOS
 */
void MetaDataFOS_text(MetaDataFOS_S* metadata){
    printf("filetype: %s\tsignature: %s\tfilename: %s\n",metadata->fostype,metadata->signature,metadata->fosname);
}

/**
 * free chaque pointer et le data
 * @param metadata
 */
void MetaDataFOS_free(MetaDataFOS_S *metadata) {
    if (metadata->fostype) {
        free(metadata->fostype);
        metadata->fostype = NULL;
    }

    if (metadata->signature) {
        free(metadata->signature);
        metadata->signature = NULL;
    }

    if (metadata->fosname) {
        free(metadata->fosname);
        metadata->fosname = NULL;
    }
}