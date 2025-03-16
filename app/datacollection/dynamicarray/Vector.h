#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_SIZE 20
/*
Construit pour le plaisir,
data est la memoire alloc 
size est le nombre de valeur dans le vector
capacite est le nombre maximal d'unite possible

quand size est egal a capacite capacite augmente de 1.5x
*/
struct StringVector{
    unsigned char* data;
    int size;
    int capacity;
}; 

int init(StringVector* v);   
int push_back(StringVector* v, unsigned char* data);

