#include "Seed_struct.h"
#include "stdio.h"
#include "stdlib.h"
//error type
#define FILETYPE    2
#define FOLDERTYPE  3
//FOS

FOS FOS_init(const char* filename, const char *path, int type){
    FOS fos = {0}; 

    fos.filename = strdup(filename);
    if (!fos.filename) return fos;

    fos.path = strdup(path);
    if (!fos.path) {
        free(fos.filename);
        fos.filename = NULL;
        return fos;
    }

    fos.type = type;
    return fos;
}

FOS_free(FOS *fos){
    free(fos->filename);
    free(fos->path);
    free(fos);
}
//file

FILE_s *FILE_init(const char* filename, const char *path) {
    FILE_s *file = malloc(sizeof(FILE_s));
    if (!file) return NULL;

    file->metadata = FOS_init(filename, path, FILETYPE);

    if(!file->metadata.filename || !file->metadata.path) {
        if (file->metadata.filename) free(file->metadata.filename);
        if (file->metadata.path)     free(file->metadata.path);
        free(file);
        return NULL;
    }

    return file;
}

//folder

FOLDER_s *FOLDER_init(const char* filename, const char *path){
    FOLDER_s *folder = malloc(sizeof(FOLDER_s));
    if(!folder) return NULL;

    folder->metadata = FOS_init(filename, path, FOLDERTYPE);

    if(!folder->metadata.filename || !folder->metadata.path) {
        if (folder->metadata.filename) free(folder->metadata.filename);
        if (folder->metadata.path)     free(folder->metadata.path);
        free(folder);
        return NULL;
    }

    return folder;
}

int ADD_FILE_CONTENT(FOLDER_s *folder, const char *filename, const char *path){
    folder->
}

int ADD_FOLDER_CONTENT(FOLDER_s *folder, const char *filename, const char *path){

}
