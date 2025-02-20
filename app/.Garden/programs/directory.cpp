#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "tree.cpp"
#include<openssl/sha.h>
/*
Objectif de se fichier 
Prendre mon object filesystem et iterer a travers le document file

ensuite je veux le mettre dans un tree

et du tree je veux hash

premiere etape et d'utiliser iterator de la class filesystem 
1- je vais simplement prendre un directory et le inserer dans un tree

pourquoi le tree?
le tree faciliteras la modification ou la transformation des donnes

2- ensuite je copierai le tree dans un autre directory

et par la suite je transformerai le tree en hashtree
*/
using namespace std;
namespace fs = std::filesystem;


//fonctionnalite commit toute les chagement ou en ceux qu'on veut
class fileSystemHandler{
    private:
    //vas etre current_path
    fs::path mainpath;

    Tree file_system=  Tree(mainpath);

    
     fs::path getRoot(){
         return fs::current_path();
     }
    public:
    //constructeur
    fileSystemHandler():mainpath(getRoot()) {};

    void printTree(Node * node){
        for(auto child : node->getNodeList()){
            if(child->getIsDirectory()==true){
                cout<<"folder: "<< child->getPath().filename()<<"\n";
                printTree(child);
            } else {
                cout<<"file: "<< child->getPath().filename()<<"\n";
            }
        }
    }
   
    
};

int main(){
    fs::path mainpath="C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\folderProjecttest";

    Tree filesystem= Tree(mainpath);


    fileSystemHandler sys;

    sys.printTree(filesystem.root);
    cin.get();
}

