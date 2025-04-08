#include"GenericVector.h"


 int init(GenericVector *vec,size_t capaciteinitial){
    
    vec->data = (void**)malloc(capaciteinitial * sizeof(void *));
    if (vec->data == NULL) {
        return 0;
    }
    vec->size = 0;
    vec->capacity =capaciteinitial;
    return 1;
 };

 int pushback(GenericVector *vec, void *data){
    if(vec->size == vec->capacity){
        //resize
        size_t new_capacity = (int)(vec->capacity * 1.25);
        if (new_capacity <= vec->capacity) { 
            new_capacity = vec->capacity + 1; 
        }

        void** temp = (void**)realloc(vec->data,new_capacity * sizeof(void *));
        if (temp==NULL){
            return 0;
        }

        vec->data = temp;
        vec->capacity = new_capacity;
    }
    vec->data[vec->size] = data;
    vec->size++;
    return 1;
 }

  int get(GenericVector*vec ,int index, void** data){
    if(index<vec->size)//assure que la taille est dans le scope de vector
        *data = vec->data[index];//prend le pointeur de vec->data
    else {
        return 0;
    }
    if(data == NULL){
        return 0;
    }
    return 1;
 }

 void freeVector(GenericVector*vec){
    if(vec != NULL){
        free(vec->data);
        free(vec);
    }
 }
