#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include "../datacollection/dynamicarray/Vector.h"
#include "../garden_tags/GardenTag.h"

using namespace std;
namespace fs = std::filesystem;


int getline(FILE* fptr,unsigned char *hash);
int HtoS(const unsigned char* hash,char* buffer);
int fileHash(const char *filename,char* buffer);
int tagHashing(GardenTag_s *tag, unsigned char (*hash)[HASH_SIZE]);
