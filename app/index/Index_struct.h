#pragma once

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
  char signature[41];
  char *name;
} Branch;

typedef struct {
    char *current_branch;
    Branch *branch_heads;
    int num_branches;
} Index_s;

#ifdef __cplusplus
}
#endif