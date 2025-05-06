#pragma once
#define HASH_BYTES_SIZE 20
#define HASH_STR_SIZE (HASH_BYTES_SIZE * 2 + 1)
// tell cpp compiler to compile in C
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char *filename;
    char *path;
    int type;
} FOS;

typedef struct {
    char hash[HASH_STR_SIZE];
    FOS metadata;
} FILE_s;

typedef struct {
    char hash[HASH_STR_SIZE];
    FOS metadata;
    FILE_s *file_list;
    int file_count;
    int file_capacity;
    FOLDER_s*folder_list;
    int folder_count;
    int folder_capacity;
} FOLDER_s;


FOS FOS_init();

FILE_s *FILE_init();

FOLDER_s *FOLDER_init();

#ifdef __cplusplus
}
#endif
