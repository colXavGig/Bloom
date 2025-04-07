#pragma once

#include "Hashing.h"
#include "../garden_tags/GardenTag.h"


void append_buffer(string *buffer, unsigned char src[HASH_SIZE]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        *buffer += src[i];
    }
}

int tagHashing(GardenTag_s *tag, unsigned char (*hash)[HASH_SIZE]) {
    string buff_hash = "";
    unsigned char md[HASH_SIZE];


    string signature = tag->signature;
    SHA1((const unsigned char *)tag->signature, sizeof(tag->signature), md);
    append_buffer(&buff_hash, md);
    SHA1(
        (const unsigned char *)ctime((const time_t *)(&tag->timestamp)),
        sizeof(tag->timestamp),
        md
    );
    append_buffer(&buff_hash, md);
    SHA1((const unsigned char *)tag->message,sizeof(tag->message), md);
    append_buffer(&buff_hash, md);

    SHA1((const unsigned char *)buff_hash.c_str(), sizeof(buff_hash.c_str()), *hash);

    return 0;
}
