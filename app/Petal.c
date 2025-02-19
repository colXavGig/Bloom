#include "Petal.h"


Petal *get_petal(FILE *file) {
    char *line;
    int line_len;
    if (getline(line, &line_len, file) != 0) {
        free(file);
        perror("Could not get doccument line\n");
        exit(2);
    }
        
    Petal *petal = (Petal *)malloc(sizeof(Petal));
    if (petal == NULL) {
        free(file);
        perror("Could not allocate memory for petal\n");
        exit(1);
    }

    SHA1((const unsigned char *)line, line_len, petal->hash);

    petal->line.value = (char (*)[])malloc(sizeof(char[line_len]));
    if (petal == NULL) {
        free(file);
        free(petal);
        perror("Could not allocate memory for char array\n");
        exit(1);
    }

    petal->line.value = line;
    petal->line.len = line_len;
       
    return petal;
}

void free_petal(Petal *petal) {
    free_string(&petal->line);
}