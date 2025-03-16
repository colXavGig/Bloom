#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "../datacollection/dynamicarray/Vector.h"


int getline(FILE* fptr,unsigned char *hash);
int fileHash(const char *filename, unsigned char* hash);