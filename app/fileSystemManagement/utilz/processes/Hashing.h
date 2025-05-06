#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <filesystem>
#include <openssl/sha.h>
#include "HashVector.h"

using namespace std;


int getlineHash(FILE* fptr,unsigned char *hash);
int HtoS(const unsigned char* hash,char* buffer);
int fileHash(const char *filename,char* buffer);
