#include "FunctionStack.h"
#include "../Juxtapose.h"

void FunctionStack::push(task *t){
    if(size == capacity){
        capacity++;
        list = (task**)realloc(list, capacity * sizeof(task));
        if (!list) {
            throw std::bad_alloc();
        }
    }
    list[size++] = t;
}

bool FunctionStack::Trypop(task *&out){
    if (size < 0) return false;
        out = list[size--];
    return true;
}

