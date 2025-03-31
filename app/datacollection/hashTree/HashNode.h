#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>

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
    protected:
        string signature; 
        string filename;   
        fs::path path; 
        //constructor
        HashNode(const fs::path &p):path(p),filename(p.filename().string()){}
    public:
        //setters
        virtual void setSignature()=0;

        void setPath(fs::path path){
            this->path=path;
        }       
        //getters
        string getSignature() const{
            return this->signature;
        }
        fs::path getPath() const {
            return this->path;
        }
        string getFileName() const{
            return this->filename;
        }
 };


 class FileNode :public HashNode{
    public:
    void setSignature();
    FileNode(const fs::path &p):HashNode(p){
        setSignature();
    }
    
 };


 class FolderNode :public HashNode{
    private:
        //afin d'eviter le dynamic casting je fais deux vector 
        //un pour files et l'autre pour fichier
        vector<FileNode *> fileNodes;
        vector<FolderNode *> folderNodes;
        string fullhash();
    public:
        void setSignature();

        FolderNode(const fs::path &p):HashNode(p){ }
        
        vector<FileNode *> getFiles()const {
            return this->fileNodes;
        }

        vector<FolderNode *> getFolders()const {
            return this->folderNodes;
        }

        void addfile(FileNode *node){
            fileNodes.push_back(node);
        }
        void addfolder(FolderNode *node){
            folderNodes.push_back(node);
        }
 };