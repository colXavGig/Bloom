#include <iostream>
#include <filesystem>
#include <vector>


namespace fs=std::filesystem;
using namespace std;

class Node{
    private:
        fs::path path;
        vector<Node*> node_list;
        bool is_directory;

        //setters
        void setDirectory(bool is_dir){
            if(is_dir){
                is_directory = true;
                node_list =  vector<Node*>();
            } else {
                is_directory = false;
                node_list.clear();
            }
        }
        
       
        
    public:
        Node(fs::path p ,bool is_dir):path(p) {setDirectory(is_dir);}

        //getters 
        fs::path getPath(){return path;}

        bool getIsDirectory(){return is_directory;}
        
        vector<Node*> getNodeList(){return node_list;}

        //fonction
        void addNode(Node* node){
            if(is_directory){
            node_list.push_back(node);
            } else {
                cerr<<"leaf can't add a a node.";
            }
    }
};

class Tree{
    private:
       
        //creation de l'arbre trouver ce genre de structure en ligne je ne suis pas un genie ahaha 
        //je l'ai adapte pour qu'elle soit bonne pour notre structure
        void createTree(Node* node){
            //si un leaf retourne
            if(node->getIsDirectory()==false)return;
            
            //si est un directory
            for(auto &entry : fs::directory_iterator(node->getPath()) ){
                
                bool is_dir=fs::is_directory(entry);
                //creation du prochain node
                Node *child_node=new Node (entry.path(),is_dir);
                //regarder dans se node
                createTree(child_node);
                //doit trouver un moyen de optimiser la memoire je checkerai sur ce sujet aujourdhui
                node->addNode(child_node);
            }
        }
    public:
    Node* root;
        Tree(fs::path p) {
            bool is_dir=fs::is_directory(p);
            root=new Node(p,is_dir);
             createTree(root);
        }
        

    
};