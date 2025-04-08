#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <openssl/sha.h>
#include "../datacollection/dynamicarray/Vector.h"
#include "../garden_tags/GardenTags.h"


int getline(FILE* fptr,unsigned char *hash);
int HtoS(const unsigned char* hash,char* buffer);
int fileHash(const char *filename,char* buffer);
int tagHashing(GardenTag *tag, unsigned char (*hash)[HASH_SIZE]);
