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