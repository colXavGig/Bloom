#include "String.h"

String *newString(char chars[], int len) {
    String *s = (String *)malloc(sizeof(String));
    if (s == NULL) {
        printf("Could not allocate memory for String '%s`\n", chars );
        exit(1);
    }

    char (*val)[len] = (char (*)[])malloc(sizeof(char[len]));
    if (val == NULL) {
        free(s);
        printf("Could not allocate memory for the array pointer\n");
        exit(1);
    }
    for (int i=0; i<len; i++) {
        (*val)[i] = chars[i];
    }

    s->len = len;
    s->value = val;

    return s;
}

void free_string(String *s) {
    free(s->value);
}