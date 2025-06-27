#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <openssl/sha.h>
#include "c_vector.h"

using namespace std;


int getlineHash(FILE* fptr,unsigned char *hash);
int HtoS(const unsigned char* hash,char* buffer);
int fileHash(const char *filename,char* buffer);
