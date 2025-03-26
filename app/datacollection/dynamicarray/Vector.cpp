#include "Vector.h"

/*
initialisation du vector capacite automatique mit a 5 
donc pour le data on malloc capacite * taille de ce qu'on veut alloc 
dans mon cas 20 bytes
*/
int init(struct StringVector *vec){
    vec->capacity=5;
    vec->data=(unsigned char*)malloc(vec->capacity*HASH_SIZE);
    vec->size=0;
    return 1;
};

/*
prends une copie du data et le mets dans le vector
en consequence son size est incrementer si le size est egal a sa capacite
realloc a lieu donc elle alloc sa nouvelle capacite
*/
int push_back(struct StringVector *vec,unsigned char* data){
  
    //Si il est rempli, la capacite du vector est augmente de 1.25x 
    if(vec->size==vec->capacity){
        size_t new_capacity= vec->capacity + (vec->capacity/4);
        unsigned char* temp=(unsigned char*)realloc(vec->data,new_capacity*HASH_SIZE);
        if(temp == NULL){
            printf("allocation de memoire failed");
            return 0;
        }
        vec->capacity = new_capacity;
        vec->data = temp;
    } 
    memcpy(vec->data + (vec->size * HASH_SIZE), data, HASH_SIZE); 
    vec->size++;
    return 1;
}
