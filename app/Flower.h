#pragma once

#include "Hash.h"
#include "Petal.h"
#include "Array_context.h"
#include "String.h"
#include "file_utils.h"

typedef struct Flower {
    Hash hash;
    Petal *(*petals)[];
    Array_ctx petals_ctx;
} Flower;

Flower *get_flower(String path);
void free_flower(Flower *flower);