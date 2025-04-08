#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <openssl/sha.h>
#include "../datacollection/dynamicarray/Vector.h"

using namespace std;


int getline(FILE* fptr,unsigned char *hash);
int HtoS(const unsigned char* hash,char* buffer);
int fileHash(const char *filename,char* buffer);
