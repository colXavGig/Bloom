
typedef struct seed {
	char *hash;
	char *signature;
	char *branch;
	struct seed *parent_hash;
} Seed;

typedef struct {
	Seed *current;
	Seed *end;
} SeedTree;

