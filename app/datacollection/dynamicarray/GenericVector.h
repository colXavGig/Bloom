#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef T
#define T void
#endif
#ifndef TVector
#define TVector VoidVector
#endif


typedef struct TVector {
    T* data;
    int size;
    int capacity;
} TVector;

int TVector_init(TVector* v);
int TVector_push(TVector* v, T* data);

