#include "GenericVector.h"

/*
initialisation du vector capacite automatique mit a 5
donc pour le data on malloc capacite * taille de ce qu'on veut alloc
dans mon cas 20 bytes
*/
#if T == void
#define CAST char
#define SIZEOF_T sizeof(char)
#else
#define CAST T
#define SIZEOF_T sizeof(T)
#endif

int TVector_init(TVector *vec) {
    vec->capacity=5;
    vec->data=(T*)malloc(vec->capacity* SIZEOF_T);
    vec->size=0;
    return 1;
};

int TVector_push(TVector *vec, T* data) {

    //Si il est rempli, la capacite du vector double
    if (vec->size==vec->capacity) {
        size_t new_capacity= vec->capacity * 2;
        T* temp = (T*)realloc(vec->data, new_capacity * SIZEOF_T);
        if (temp == NULL) {
            printf("allocation de memoire failed");
            return 0;
        }
        vec->capacity = new_capacity;
        vec->data = temp;
    }
    memcpy((CAST*)vec->data + (vec->size * SIZEOF_T), data, SIZEOF_T);
    vec->size++;
    return 1;
}
