#pragma once

#include "Hashing.h"
#include "../garden_tags/GardenTag.h"


void append_buffer(string *buffer, unsigned char src[HASH_SIZE]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        *buffer += src[i];
    }
}

int tagHashing(GardenTag_s* tag, char (*hash)[HASH_SIZE + HASH_SIZE + 1]) {
    string buff_hash = "";
    unsigned char md[HASH_SIZE];

    // Hash root signature
    SHA1((const unsigned char*)tag->root->signature, strlen(tag->root->signature), md);
    append_buffer(&buff_hash, md);

    // Hash tag message
    SHA1((const unsigned char*)tag->message, strlen(tag->message), md);
    append_buffer(&buff_hash, md);

    // Hash the combined buffer
    SHA1((const unsigned char*)buff_hash.c_str(), buff_hash.size(), md);

    // Convert final hash to string
    HtoS(md, *hash);

    return 0;
}
