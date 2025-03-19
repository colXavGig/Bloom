#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>
#include "../../processes/Hashing.h"
#include <openssl/sha.h>
using namespace std;
namespace fs=std::filesystem;
/*
node qui hash son contenue dependament de son type (dir/fichier)
elle hash les lignes des fichier pour ensuite les concat et hash le concat
if it's a folder it will hash concatenate the hash of the files it contains and hash it.

1 responsibilities assurer que fichiers et folder peuvent etre adequatement represente:
Propriete 1: le nom du dir/fichier
Propriete 2: le hash du dir/fichier
propriete 3:
*/
class HashNode{
    private:
        bool isfile;
        vector<HashNode *> hnode_array;
        string signature;
        fs::path path;
        string name;

        //helper functions
        void HtoS(const unsigned char* hash);
        string fullhash();
        void HashString(const string& s);
    public:
        //constructeur
        vector<HashNode *> getNodeArray()const {
            return this->hnode_array;
        }
        //setters
        void setSignature(const char *path);

        void setIsFile(bool b){
            this->isfile=b;
        }
        void setPath(fs::path path){
            this->path=path;
        }
        void setNode(HashNode * node){
            hnode_array.push_back(node);
        }
        //getters
        bool getIsFile() const{
            return this->isfile;
        }
        string getSignature() const{
            return this->signature;
        }
        fs::path getPath() const {
            return this->path;
        }
 };