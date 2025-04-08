#pragma once

// tell cpp compiler to compile in C
#ifdef __cplusplus
extern "C" {
#endif

typedef union HashNode_content HashNode_content;

typedef struct HashNode_s {
    char *signature;
    char *filename;
    char *path;
    int type;
    HashNode_content *content;
} HashNode_s;

typedef struct {
    int type;
    HashNode_s *subItems;
} FolderNode_content;

union HashNode_content {
    char *file_content;
    FolderNode_content *folder_contents;
};

#ifdef __cplusplus
}
#endif
