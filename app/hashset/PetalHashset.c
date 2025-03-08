
#include "Petal.h"
#include "Array_context.h"

#define HASHSET_LEN 256

typedef struct PetalNode {
    Petal petal;
    int next;
} PetalNode;


typedef struct {
    PetalNode hashset[HASHSET_LEN];
    Array_ctx list_ctx;
    PetalNode (*linklist)[];
}PetalSet;

static PetalSet petals;

void PetalSet_init() {
    petals = (PetalSet) {
        .list_ctx = (Array_ctx) {
            .length = 0,
            .capacity = 0,
        },
        .linklist = NULL,
    };

    for (int i =0; i < HASHSET_LEN; i++) {
        petals.hashset[i].petal.line.len = -1;
    }
}

int PetalSet_add(Petal ptl) {
    int code = generate_hascode(ptl.hash);
    int position = code % HASHSET_LEN;

    if (petals.hashset[position].petal.line.len == -1) {
        petals.hashset[position] = (PetalNode) {
            .petal = ptl,
            .next = -1,
        };
        return 0;
    }
    
    PetalNode *curr = &petals.hashset[position];

    while (curr->next != -1) {
        curr = &(*petals.linklist)[curr->next];
    }

    int next = PetalSet_add_to_list(ptl);
    if (next < 0) {
        return next;
    }

    curr->next = next;
    return 0;
}

int PetalSet_add_to_list(Petal ptl) {
    if (petals.linklist == NULL) {
        petals.linklist = (PetalNode(*)[])malloc(sizeof(PetalNode) * 10);
        if (petals.linklist == NULL) {
            return -1;
        }

        petals.list_ctx.capacity = 10;
        petals.list_ctx.length = 0;
    }

    if (petals.list_ctx.capacity <= petals.list_ctx.length + 1) {
        PetalNode (*newList)[] = (PetalNode(*)[])realloc(
            petals.linklist,
            sizeof(PetalNode) * (petals.list_ctx.capacity * 2)
        );

        if ( newList == NULL) {
            free(petals.linklist);
            return -2;
        }

        petals.linklist = newList;
        petals.list_ctx.capacity *= 2;
    }

    (*petals.linklist)[petals.list_ctx.length] = (PetalNode) {
        .petal = ptl,
        .next = -1,
    };
    return petals.list_ctx.length++;
}
