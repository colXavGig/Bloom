#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char *current_branch;
    char **branch_heads;
} Index_s;

#ifdef __cplusplus
}
#endif