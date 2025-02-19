#include "file_utils.h"

char fpeek(FILE *file) {
    char c = fgetc(file);
    ungetc(c, file);
    return c;
}