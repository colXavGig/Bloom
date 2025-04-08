#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **data;
    size_t size;
    size_t capacity; 
 } GenericVector; 

 int genericvector_init(GenericVector *vec,size_t capaciteinitial);
 int pushback(GenericVector *vec, void *data);
 int get(GenericVector*vec ,int index, void** data);
 void freeVector(GenericVector*vec);
