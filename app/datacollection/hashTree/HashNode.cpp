#include "HashNode.h"
using namespace std;
        /*
         Fonction qui convertit hash to string
        */
        void HashNode::HtoS(const unsigned char* hash){
            for (int i = 0; i < 20; i++) {
                char buf[3]; 
                sprintf(buf, "%02x", hash[i]);
                this->signature += buf;
            }
        }

        /*
        Prends les hash de chaques node dans le node_array et les concat
        */
        string HashNode:: fullhash(){
            stringstream ss;
            for(HashNode *hnode : this->getNodeArray()){
                if(!hnode->getSignature().empty())
                    ss<<hnode->getSignature();
            }
            return ss.str();
        }
        /*
        fonction utilise pour hasher les folders, il prends un string et le hash
        ensuite le reconvertit en string. 
        */
        void HashNode::HashString(const string& s){
            unsigned char hash[SHA_DIGEST_LENGTH];  
            SHA1(reinterpret_cast<const unsigned char*>(s.c_str()), s.size(), hash);
            HtoS(hash);
        }
    //setters
    /*
    Cette fonction dependament du type de node quelle est,
    vas Hash d'une maniere differente:
    ficher son contenu ( ces lignes )
    folder son contenu ( ces fichiers )
    */
    void HashNode::setSignature(const char *path){
        unsigned char hash[20];
        if(isfile==true){
            fileHash(path,hash);
            this->HtoS(hash);
        } else {
            string str=fullhash();
            if(!str.empty())
                this->HashString(str);
        }
    }
   
    
