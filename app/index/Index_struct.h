#pragma once

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
  char signature[41];
  char *name;
} Branch;

struct Index_s{
    char *current_branch;
    Branch *branch_heads;
    int num_branches;

    Index_s():current_branch('main'), branch_heads(nullptr), num_branches(0){

    };
};

#ifdef __cplusplus
}
#endif