#include <string.h>
#include <stdio.h>
#include "string.cpp"
#include <openssl/sha.h>

typedef unsigned char Hash[SHA_DIGEST_LENGTH];

typedef struct {
    Hash hash;
    String line;
} Petal;

Petal get_petal(FILE *file_ptr) {
    String line;
    getline(
        &line.value,
        &line.len,
        file_ptr 
        );
    Hash hash;
    SHA1((const unsigned char *)line.value, line.len, hash);

    return Petal{
        .hash = *hash,
        .line = line,
    };
}