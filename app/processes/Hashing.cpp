#include "Hashing.h"

//boolean
#define TRUE 1
#define FALSE 0
//hash size
#define HASH_SIZE 20
//line / file size
#define LINE_SIZE 1000
/*pseudo code de getline
    chercher un char 
    assurer qu'il n'est pas EOF
*/

    int getlineHash(FILE* fptr, unsigned char* hash) { 
        unsigned char line[LINE_SIZE];
        int i = 0;
        int c;
    
        while ((c = fgetc(fptr)) != EOF && c != '\n') {
            line[i++] = c;
        }
        line[i] = '\0';
    
        if (i > 0 || c == '\n') {
            SHA1(line, strlen((char*)line), hash);
            return TRUE;
        }
    
        return FALSE;
    }

/*
    Fonction qui convertit hash to string

    SHA1 fait un 20bytes long hex (0,255) -> donc pour etre capable de transformer le hex en char
    on doit allocer 2 char.
*/
int HtoS(const unsigned char* hash,char* buffer){
    
    for (int i = 0; i < HASH_SIZE; i++) {
        sprintf(buffer + (i *2), "%02x", hash[i]);  
    };

    return 1;
}

/*  pseudo code du HashedList
    while ( getline(une ligne, taille maximal de la ligne) est vrai )
        hash -> ligne
        inserer hash dans la liste
*/
//takes a file and hashes it
int fileHash(const char *filename,char* buffer){
    unsigned char hash[HASH_SIZE];
    HashVector vec;
    //openFile read-only
    FILE *fptr = fopen(filename,"r");
    //assurer que le pointer n'est pas null
    if(fptr==NULL){
      printf("File doesn't exist :(");
    }
    //initialisation du data
    HashVector_init(&vec);  
    while(getlineHash(fptr,hash)){
        HashVector_pushback(&vec,hash);
    }
    fclose(fptr);
    SHA1(vec.data, vec.size * HASH_SIZE, hash);   
    HtoS(hash,buffer);

    return 1;
}
