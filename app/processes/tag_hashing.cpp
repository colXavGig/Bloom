//
// Created by bebew on 2025-04-07.
//
#include "Hashing.h"
#include "../garden_tags/GardenTag.h"


void append_buffer(string *buffer, unsigned char src[HASH_SIZE]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        *buffer += src[i];
    }
}

int tagHashing(GardenTag *tag, unsigned char (*hash)[HASH_SIZE]) {
    string buff_hash = "";
    unsigned char md[HASH_SIZE];


    string signature = tag->getRootHash();
    SHA1((const unsigned char *)signature.c_str(), sizeof(signature.c_str()), md);
    append_buffer(&buff_hash, md);
    SHA1(
        (const unsigned char *)ctime((const time_t *)(&tag->timestamp)),
        sizeof(tag->timestamp),
        md
    );
    append_buffer(&buff_hash, md);
    SHA1((const unsigned char *)tag->message.c_str(),sizeof(tag->message.c_str()), md);
    append_buffer(&buff_hash, md);

    SHA1((const unsigned char *)buff_hash.c_str(), sizeof(buff_hash.c_str()), *hash);

    return 0;
}
