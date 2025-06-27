#include "Hashing.h"
#define TRUE 1
#define FALSE 0
#define HASH_SIZE 20
#define LINE_SIZE 256
/*pseudo code de getline
    chercher un char 
    assurer qu'il n'est pas EOF
*/

    int getlineHash(FILE* fptr, unsigned char* hash) { 
        unsigned char line[LINE_SIZE];
        int i = 0;
        int c;
        while((c =fgetc(fptr)) != EOF && c !='\n' && i != LINE_SIZE-1) {
             line[i++]=c;
        }          
        line[i] = '\0';//finish string
    
        if (i > 0 || c == '\n') {
            SHA1(line, i, hash);
            return TRUE;
        }
    
        return FALSE;
    }

/*
    Fonction qui convertit hash to string

    SHA1 fait un 20bytes long hex (0,255) -> donc pour etre capable de transformer le hex en char
    on doit allocer 2 char.
*/
int hash_to_string(const unsigned char* hash,char* buffer){
    
    for (int i = 0; i < HASH_SIZE; i++) {
        sprintf(buffer + (i *2), "%02x", hash[i]);  
    };
    buffer[HASH_SIZE * 2] = '\0';
    return 1;
}

/*  pseudo code du HashedList
    while ( getline(une ligne, taille maximal de la ligne) est vrai )
        hash -> ligne
        inserer hash dans la liste
*/

int fileHash(const char *filename,char* buffer){
    unsigned char hash[HASH_SIZE];

    //openFile read-only
    FILE *fptr = fopen(filename,"r");
    //assurer que le pointer n'est pas null
    if(fptr==NULL){
      printf("File doesn't exist :(");
    }    
    //initialisation du data    
    c_vector vec;

    vector_heap_init(&vec);  

    while(getlineHash(fptr,hash))
        vector_pushback(&vec,hash);

    fclose(fptr);
    SHA1(vec.data, vec.size * HASH_SIZE, hash);   
    HtoS(hash,buffer);
    
    vector_free(&vec);
    return 1;
}
