#include "HashVector.h"
/** 
* initialisation du vector capacite automatique mit a 5.
* Donc pour le data on malloc capacite * taille de ce qu'on veut alloc 
* dans mon cas 20 bytes
* @throw bad_alloc_exception if malloc fails
* @return 1 if succes
*/
int vector_heap_init(c_vector *vec){
    vec->capacity=20;
    vec->data=(unsigned char*)malloc(vec->capacity*HASH_SIZE);
    if(!vec->data){
        throw std::bad_alloc();
    }
    vec->size=0;
    return 1;
};

/** 
* prends une copie du data et le mets dans le vector
* en consequence son size est incrementer si le size est egal a sa capacite
* @todo make sure data of size 20 bytes 
* @param vec
* @param data hash data that needs to be of size 20bytes;
* @throw bad_alloc_exception if realloc fails
* @return 1 if succes
*/
int vector_pushback(c_vector *vec,unsigned char* data){
  
    //Si il est rempli, la capacite du vector est augmente de 1.25x 
    if(vec->size==vec->capacity){
        size_t new_capacity= vec->capacity + (vec->capacity/4);
        unsigned char* temp=(unsigned char*)realloc(vec->data,new_capacity*HASH_SIZE);
        if(!temp){
            throw std::bad_alloc();
        }
        vec->capacity = new_capacity;
        vec->data = temp;
    } 
    memcpy(vec->data + (vec->size * HASH_SIZE), data, HASH_SIZE); 
    vec->size++;
    return 1;
}

void vector_free(c_vector *vec){
  free(vec->data);
  free(vec); 
}
