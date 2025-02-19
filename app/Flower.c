#include "Flower.h"

Flower *get_flower(String path) {
    FILE *file = fopen(path.value, 'r');

    Flower *flower = malloc(sizeof(Flower));
    if (flower == NULL) {
        fclose(file);
        perror("Could not allocate memory for flower\n");
        exit(1);
    }

    Petal *(*petals)[] = (Petal *(*)[])malloc(sizeof(Petal *[8]));
    if (petals == NULL) {
        free(flower);
        fclose(file);
        perror("Could not allocate memory for petals array\n");
        exit(1);
    }

    flower->petals = petals;
    flower->petals_ctx.length = 0;
    flower->petals_ctx.capacity = 8;

    SHA_CTX ctx;
    if (SHA1_Init(&ctx) != 0) {
        free_flower(flower);
        free(flower);
        fclose(file);
        perror("Could not init flower hashing\n");
        exit(1);
    }

    while (fpeek(file) != EOF) {
        Petal *petal = get_petal(file);
        if (add_petal(flower, petal) != 0) {
            fclose(file);
            free_flower(flower);
            free(flower);

            perror("Could not add petal");
            exit(2);
        }

        if (SHA1_Update(&ctx, petal->hash, SHA_DIGEST_LENGTH) != 0) {
            fclose(file);
            free_flower(flower);
            free(flower);

            perror("Could not add petal to the hash context");
            exit(3);
        }
    }
    fclose(file);

    if (SHA1_Final(flower->hash, &ctx) != 0) {
        free_flower(flower);
        free(flower);

        perror("Could not compute hash for flower\n");
        exit(3);
    }
    
    return flower;
}

int add_petal(Flower *flower, Petal *petal ) {
    if (flower->petals_ctx.length+1 > flower->petals_ctx.capacity) {

        Petal *(*new_petals)[] = (Petal *(*)[])realloc(flower->petals, sizeof(Petal*[flower->petals_ctx.capacity * 2]));
        if (new_petals == NULL) {
            free(flower->petals);
            perror("Realloc failed while adding petal to flower");
            return 1;
        }
        flower->petals = new_petals;
        flower->petals_ctx.capacity *= 2;
    }

    (*flower->petals)[flower->petals_ctx.length] = petal;
    flower->petals_ctx.length++;

    return 0;
}

void free_flower(Flower *flower) {
    for (int i=0; i<flower->petals_ctx.length; i++) {
        free_petal((*flower->petals)[i]);
        free((*flower->petals)[i]);
    }
    free(flower->petals);
}