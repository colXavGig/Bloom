#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <openssl/sha.h>

#include "c/HashNode_struct.h"

using namespace std;
namespace fs=std::filesystem;

#define FILENODE 1
#define FOLDERNODE 2

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
            setSignature(signature);
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
        virtual void generateSignature() = 0;
        virtual void setContent(HashNode_content *content) =  0;

        /**
         * Set the path of the HashNode to the provided value
         * @param path The new value for the path
         */
        void setPath(fs::path path);

        /**
         * Allocate space for the filename and copy it to the structure
         * @param filename The filename of the current Node
         */
        void setFilename(string filename);

        /**
         * Allocate space for the signature and copy it to the structure
         * @param signature The hashed signature of the Node
         */
        void setSignature(string signature);
        /**
         * Deconstruct
         */
        ~HashNode();

    ///////////////////////////////////////////////////////////////////////////////

    public:

        /**
         * Ge the hashed signature of the HashNode
         * @return a string representing the hashed signature of the HashNode
         */
        string get_signature() const{
            return this->value->signature;
        }
        fs::path get_path() const {
            return this->value->path;
        }
        string get_filename() const{
            return this->value->filename;
        }

        /**
         * Get the structural data of the HashNode
         * @return a struct representing the value of the HashNode
         */
        HashNode_s *get_struct_value();

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
        generateSignature();
    }

    /**
     * Conmstruct that does not hash its signature and assigne the one provided to hime
     * @param path The path to the file which the FileNode need to represent
     * @param filename The name of te file which the node represent
     * @param signature The signature of the FileNode which is hashed string of its content
     */
    FileNode(const fs::path &path,const string filename,const string signature)
    :HashNode(path, filename, signature, FILENODE) {}

    void setContent(string content);
    void setContent(HashNode_content *content) override;


    /** Implicit conversion to HashNode_s pointer */
    operator HashNode_s *() const {
        return value;
    }

    ////////////////////////////////////////////////////////////////////////

    private:
        void generateSignature() override;
 };


class FolderNode :public HashNode{

    public:
        void generateSignature() override;

        FolderNode(HashNode_s *value): HashNode(value) {}
        //constructeur
        FolderNode(const fs::path &p):HashNode(p, FOLDERNODE) {}

        //constructeur de garden--> ne hash rien
        FolderNode(const fs::path &path,const string &filename,const string &signature):
            HashNode(path, filename, signature, FOLDERNODE) {}


        vector<FileNode *> get_files()const {
            return this->fileNodes;
        }

        vector<FolderNode *> get_folders()const {
            return this->folderNodes;
        }

        void add_file(FileNode *node){
            fileNodes.push_back(node);
        }
        void add_folder(FolderNode *node){
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



