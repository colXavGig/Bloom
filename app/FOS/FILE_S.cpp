#include "FILE_S.h"
#define PARENT 0
#define CHILD  1

LINE *LINE_init(int number, char *pline, char *cline){
    LINE *temp = (LINE *)malloc(sizeof(LINE));
    temp->number = number;
    temp->diff[PARENT] = strdup(pline);
    temp->diff[CHILD] = strdup(cline);
    return temp;
}


FILE_S *FILE_createFile(const char *type,const char *filename,const char *path){
    FILE_S *temp = (FILE_S*)malloc(sizeof(FILE_S));
    temp->type = strdup(type);
    temp->filename = strdup(filename);
    temp->path = strdup(path);
    temp->capacity =20;
    temp->size = 0;
    temp->contained = (LINE*)malloc(temp->capacity * sizeof(LINE));
    if(!temp->contained){
        throw std::bad_alloc();
    }
    
    return temp;
}

void FILE_AddLine(FILE_S *file, LINE *line){

    if(file->size == file->capacity){
        file->capacity *= 2; 
        file->contained =(LINE*)realloc(file->contained,file->capacity * sizeof(LINE));
        if(!file->contained){
            throw std::bad_alloc();
        }
    }
    file->contained[file->size].number = line->number;
    file->contained[file->size].diff[0] = strdup(line->diff[0]);
    file->contained[file->size].diff[1] = strdup(line->diff[1]);
    file->size++;
}



LINE FILE_getLINE(FILE_S *file, size_t index){
    if (!file || index >= file->size)
        throw  std::out_of_range("size not big enough");

    return file->contained[index];
}

void FILE_READ(FILE_S *file){
    printf("METADATA:\n");
    printf("%s \t %s \t %s \n",file->type, file->filename, file->path);
    int i=0;
    while(i<file->size){
        LINE line = file->contained[i];
        printf("%d - %s  + %s\n",line.number,line.diff[0],line.diff[1]);
        i++;
    }
}