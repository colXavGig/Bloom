#include "Array_context.h"
#include "String.h"
#include <stdio.h>

typedef struct Path
{
    String name;
    String type;

} Path;


typedef struct PathList
{
    Array_ctx ctx;
    Path (* paths)[];
} PathList;


PathList *newPathList(int capacity) {
    PathList *list = (PathList*)malloc(sizeof(PathList));
    if (list == NULL) {
        puts("Could not malloc StringList");
        return NULL;
    }

    *list = (PathList) {
        .ctx = (Array_ctx) {
            .capacity = capacity,
            .length = 0
        },
        .paths = (Path(*)[capacity]) malloc(sizeof (Path(*)[capacity])),
    };

    if (list->paths == NULL)
    {
        puts("Could not malloc String array");
        free(list);
        return NULL;
    }

    return list;
}

int PathList_add(PathList *list, Path path) {
    if (list->ctx.capacity <= list->ctx.length+1) {
        int doubledCapacity = list->ctx.capacity * 2;
        
        Path (*newList)[] = (String(*)[]) realloc(list->paths, sizeof (String(*)[doubledCapacity]));
        if (newList == NULL) {
            puts("Could not resize String array");
            free(list->paths);            
            return 1;
        }

        list->ctx.capacity = doubledCapacity;
        list->paths = newList;
    }

    (*list->paths)[list->ctx.length] = path;
    list->ctx.length++;

    return 0;
}