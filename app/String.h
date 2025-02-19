#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct {
    char (*value)[];
    size_t len;
} String;

String *newString(char * chars, int len);
void free_string(String *s);


