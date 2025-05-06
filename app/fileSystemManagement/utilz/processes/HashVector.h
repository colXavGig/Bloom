#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept> 
#define HASH_SIZE 20
/*
Construit pour le plaisir,
data est la memoire alloc 
size est le nombre de valeur dans le vector
capacite est le nombre maximal d'unite possible

quand size est egal a capacite capacite augmente de 1.5x
*/
typedef struct {
    unsigned char* data;
    int size;
    int capacity;
} HashVector; 

int HashVector_init(HashVector *v);   
int HashVector_pushback(HashVector *v, unsigned char *data);

