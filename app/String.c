#include "String.h"

String *newString(char *chars, int len) {
    String *s = (String *) malloc(sizeof(String));
    if (s == NULL) {
        printf("Could not allocate memory for String '%s`\n", chars );
        exit(1);
    }

    s->len = len;
    s->value = chars;

    return s;
}