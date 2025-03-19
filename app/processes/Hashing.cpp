#include "Hashing.h"
//boolean
#define TRUE 1
#define FALSE 0
//hash size
#define HASH_SIZE 20
//line / file size
#define LINE_SIZE 256
/*pseudo code de getline
    chercher un char 
    assurer qu'il n'est pas EOF
    assigner lettre a *line
    incrementer pointeur
*/
int getline(FILE* fptr,unsigned char *hash){ 
    unsigned char line[LINE_SIZE];
    int i=0,c;
    while((c=fgetc(fptr)) != EOF && c !='\n'){
        line[i++]=c;
    }
    line[i]='\0';
    SHA1(line,strlen((char*)line),hash);
    return (c != EOF) ? TRUE : FALSE;
}
/*  pseudo code du HashedList
    while ( getline(une ligne, taille maximal de la ligne) est vrai )
        hash -> ligne
        inserer hash dans la liste
*/
//takes a file 
int fileHash(const char *filename, unsigned char* hash){
    StringVector vec;
    //openFile read-only
    FILE *fptr = fopen(filename,"r");
    //assurer que le pointer n'est pas null
    if(fptr==NULL){
      printf("File doesn't exist :(");
    }
    //initialisation du data
    init(&vec);  
    while(getline(fptr,hash)){
        push_back(&vec,hash);
    }
    fclose(fptr);
    SHA1(vec.data, vec.size * HASH_SIZE, hash);
    return 1;
}


