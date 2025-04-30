#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//error handling
#include <stdexcept> 

typedef struct{
    int   number;
    char *diff[2];
}LINE;
/**
 * illustre FILE_S
 * 
 * === METADATA ===
 * @param type      type de changement [~] [-] [+]
 * @param filename  name of the file
 *  @param path     path of the file
 * === STATE DATA ===
 * @param contained LINE** list generic dans le but detre un FOS ou une ligne
 */
typedef struct{
    char *type;
    char *filename; 
    char *path;
    LINE *contained;
    size_t size;
    size_t capacity;
}FILE_S;




/**
 * illustre un changement sur une ligne
 * 
 * === METADATA ===
 * @param number    line number
 * @param pline     ligne du document parent
 * @param cline     ligne du document child \ head
 */
LINE *LINE_init(int number, char *pline, char *cline);

/**
 * initialise le METADATA du file
 * la taille est set a 20 et double
 */
FILE_S *FILE_createFile(const char *type,const char *filename,const char *path);

/**
 * rajouter une ligne diff
 * 
 */
void FILE_AddLine(FILE_S *file, LINE *line);

/**
 * retourne une valeur simplement si le FOS retourne une LINE
 * 
 * @param file      FILE object
 * @param index     index de la liste
 */
LINE FILE_getLINE(FILE_S *file, size_t index);

/**
 * Imprimer le state de file
 * 
 * @param file      FILE object
 */
void FILE_READ(FILE_S *file);
