#include <openssl/sha.h>

typedef unsigned char Hash[SHA_DIGEST_LENGTH];

int generate_hascode(Hash hash);