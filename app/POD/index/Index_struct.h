#pragma once
#ifdef __cplusplus
extern "C" {
#endif


typedef struct Branch{
  char hash[41];
  char *name;
  struct Branch *next;
} Branch;

typedef struct{
    Branch *current; // point a une des branches
    Branch *list;
} Index_s;

//branch manipulation

Branch *alloc_branch(const char *name, const char *hash);
int free_Index(Index_s *);
//index manipulation

int add_branch(Index_s * index, const char *name, const char *hash);
int delete_branch(Index_s* index, const char *name);
int set_current(Index_s *index, const char* name);

#ifdef __cplusplus
}
#endif
