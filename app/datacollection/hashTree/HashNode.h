#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>

#include <openssl/sha.h>
using namespace std;
namespace fs=std::filesystem;
#define FILENODE 1
#define FOLDERNODE 2

//extern "C" {
typedef union HashNode_content HashNode_content;

typedef struct HashNode_s {
    char *signature;
    char *filename;
    char *path;
    int type;
    HashNode_content *content;
} HashNode_s;

typedef struct {
    int type;
    HashNode_s *signature_node;
} FolderNode_content;

union HashNode_content {
    char *file_content;
    FolderNode_content *folder_contents;
};
//}

/**
 * node qui hash son contenue dependament de son type (dir/fichier)
 * elle hash les lignes des fichier pour ensuite les concat et hash le concat
 * if it's a folder it will hash concatenate the hash of the files it contains and hash it.
 *
 * 1 responsibilities assurer que fichiers et folder peuvent etre adequatement represente:
 * Propriete 1: le nom du dir/fichier
 * Propriete 2: le hash du dir/fichier
 * propriete 3:
 */
class HashNode {
    protected:
        /** Structural value of the HashNode */
        HashNode_s *value;
        // string signature;
        // string filename;
        // fs::path path;

        /**
         * Construct an HashNode with a pre-generated value
         * @param value The structural value of the HashNode
         */
        HashNode(HashNode_s *value) {
            this->value = value;
        }

        /**
         * Construct a HashNode with its path and the subtype of the HashNode
         * @param p The path to the node
         * @param type The subtype of the HashNode, FOLDERNODE being a FolderNode
         *      and FILENODE representing a FileNode
         */
        HashNode(const fs::path &p, const int type) {
            init(p, p.filename().string(), type);
        }

        /**
         * Construct a HashNode with its path, the filename, the signature and the subtype of the HashNode
         * @param path The path of the node
         * @param filename The filename of the node
         * @param signature The pre-hashed signature of the node
         * @param type The subtype of the HashNode, FOLDERNODE being a FolderNode
         *      and FILENODE representing a FileNode
         */
        HashNode(const fs::path path, const string filename, const string signature, const int type) {
            init(path, filename, type);
            value->signature = (char *)signature.data();
        }

        /**
         * Initiate the value of the node
         * @param path The path of the HashNode
         * @param filename The filename of the HashNode
         * @param type The subtype of the HashNode, FOLDERNODE being a FolderNode
         *      and FILENODE representing a FileNode
         */
        virtual  void init(const fs::path &path,const string filename,int type);

        /**
         * Generate and set the hashed signature of the node.
         * Implemented by the subtype
         */
        virtual void setSignature() = 0;
        virtual void setContent(HashNode_content *content) =  0;

    ///////////////////////////////////////////////////////////////////////////////

    public:
        /**
         * Set the path of the HashNode to the provided value
         * @param path The new value for the path
         */
        void setPath(fs::path path){
            this->value->path = path.string().data();
        }

        /**
         * Ge the hashed signature of the HashNode
         * @return a string representing the hashed signature of the HashNode
         */
        string getSignature() const{
            return this->value->signature;
        }
        fs::path getPath() const {
            return this->value->path;
        }
        string getFileName() const{
            return this->value->filename;
        }

        /**
         * Get the structural data of the HashNode
         * @return a struct representing the value of the HashNode
         */
        HashNode_s *getStructValue();

 };


class FileNode : public HashNode{
    public:

    /**
     * Construct a FileNode with a preconstructed value
     * @param value The value that represent the FileNode
     */
    FileNode(HashNode_s *value): HashNode(value) {
    }

    /**
     * Construct a FileNode with a path to the file
     * @param p The path to the file which the FileNode need to represent
     */
    FileNode(const fs::path &p): HashNode(p, FILENODE) {
        setSignature();
    }

    /**
     * Conmstruct that does not hash its signature and assigne the one provided to hime
     * @param path The path to the file which the FileNode need to represent
     * @param filename The name of te file which the node represent
     * @param signature The signature of the FileNode which is hashed string of its content
     */
    FileNode(const fs::path &path,const string filename,const string signature)
    :HashNode(path, filename, signature, FILENODE) {}

    void setContent(char *content);
    void setContent(HashNode_content *content) override;


    /** Implicit conversion to HashNode_s pointer */
    operator HashNode_s *() const {
        return value;
    }

    ////////////////////////////////////////////////////////////////////////

    private:
        void setSignature() override;
 };


class FolderNode :public HashNode{

    public:
        void setSignature() override;

        FolderNode(HashNode_s *value): HashNode(value) {}
        //constructeur
        FolderNode(const fs::path &p):HashNode(p, FOLDERNODE) {}

        //constructeur de garden--> ne hash rien
        FolderNode(const fs::path &path,const string &filename,const string &signature):
            HashNode(path, filename, signature, FOLDERNODE) {}


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

    private:
        //afin d'eviter le dynamic casting je fais deux vector
        //un pour files et l'autre pour fichier
        vector<FileNode *> fileNodes;

        vector<FolderNode *> folderNodes;

        /** Prends les hash de chaques node dans le node_array et les concat */
        string fullhash();
        void setContent(FolderNode_content *content);
        void setContent(HashNode_content *content) override;
 };