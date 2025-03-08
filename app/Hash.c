#include "Hash.h"

int generate_hascode(Hash hash) {
    int code = 0;

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        code = code * 31 + hash[i];
    }

    return code;
}