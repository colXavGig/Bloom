#include "Diff.h"

void Diff::add(FILE_S *f){
    if(size == capacity){
        capacity *=2;
        diff = (FILE_S*)realloc(diff,capacity * sizeof(FILE_S));

        if(!diff)throw new std::bad_alloc;   
    }
    diff[size++]=*f;
}

bool Diff:: tryRead(FILE_S out){
    if(size < 0)
        return false;
    out = diff[size--];
    return true;
}

void Diff::readAll() {
    for (int i = 0; i < size; ++i) {
        FILE_S file = diff[i];


        printf("File: %s, Type: %s\n", file.filename, file.type);

  
        for (int j = 0; j < file.size; ++j) {
            LINE line = file.contained[j];
            printf("Line %d: Parent[%s] Head[%s]\n", j, line.diff[0], line.diff[1]);
        }

        printf("\n"); 
    }
}