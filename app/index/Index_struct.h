#pragma once
#include<string.h>
#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
  char signature[41];
  char *name;
} Branch;

typedef struct Index_s{
    Branch *current_branch; // point a une des branches
    Branch *branch_heads;
    int num_branches;

} Index_s;



#ifdef __cplusplus
}
#endif