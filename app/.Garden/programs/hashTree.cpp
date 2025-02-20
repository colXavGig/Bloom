#include <filesystem>
#include <iostream>
#include <openssl/sha.h>
#include<stdio.h>
#include <vector>
#include <fstream>
namespace fs=std::filesystem;
using namespace std;

class HashedNode{
    private:
        string filename;
        unsigned char hash[SHA_DIGEST_LENGTH];
        bool is_Directory;
        vector<HashedNode*> hashed_node_list;

        void hashContent(unsigned char *fileContent,size_t filesize){
            SHA1(fileContent,filesize,hash);
        }
    public:
        HashedNode(string& filename,vector<unsigned char> &content): filename(filename){
            hashContent(content.data(), content.size());
        };


};

class HashedTree{
    private:
        fs::path file_root;
        HashedNode *tree_root;


        vector<unsigned char> GetFileContent(const fs::path& path){
            //initialisation du input stream
            ifstream ifs(path,ios_base::binary);
            //afin de pouvoir storer le contenu du file
            vector<unsigned char> content;

            unsigned char ch;
            while(ifs>>ch){
                content.push_back(ch);
            }

            return content;
        }


        void buildHashtree(HashedNode * hnode){
            if(fs::is_regular_file(file_root)){

                string filename=file_root.filename().string();
                vector<unsigned char> content = GetFileContent(file_root);
                hnode = new HashedNode (filename,content);  
            }

            for(auto &entry : fs::directory_iterator(file_root)){
                
                

            }

        }
    public:


}