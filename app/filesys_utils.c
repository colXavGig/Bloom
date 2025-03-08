#include "String.h"
#include "PathList.c"

#define OS_LINUX

#ifdef OS_LINUX

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>


String get_cwd() {
    String cwd;
    getcwd(&cwd.value, &cwd.len);
    return cwd;
}

int get_dir_content(char *path, PathList *pathList) {
    DIR *d = opendir(path);
    if (d == NULL) {
        printf("Could not open %s as dir\n", path);
        return 1;
    }

    struct dirent * de;
    while ((de = readdir(d)) != NULL)
    {
        PathList_add(
            pathList,
            (Path) {
                .name = (String) {
                    .value = de->d_name,
                    .len = strlen(de->d_name),
                },
                .type = entity_type(de->d_type),
            }
        );
    }

    closedir(d);

    return 0;
}

String entity_type(char *d_type) {
    if (strcmp(d_type, "D_DIR") == 0) {
        return (String) {
            .value = "dir",
            .len = 3,
        };
    } else if (strcmp(d_type, "D_REG")) {
        return (String) {
            .value = "file",
            .len = 4,
        };
    } else {
        return (String) {
            .value = "unknown",
            .len = 7,
        };
    }
}



#endif


