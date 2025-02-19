#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "String.h"
#include "Hash.h"

typedef struct Petal {
    Hash hash;
    String line;
} Petal;

Petal *get_petal(FILE *file);
void free_petal(Petal *petal);
