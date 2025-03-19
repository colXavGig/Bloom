#include "HashTree.h"
    /*
    Constructeur prends une directory
    et copy le filesystem a partir.
    */
    HashTree::HashTree(fs::path directory){
        createTree(&this->root,directory);  
    }

    /*
    fonction Recursive, creer le tree et set les information importantes
    pour faire la sauvegarde. 
    */
    void HashTree::createTree(HashNode *pnode,fs::path current_directory){
        cout<<"Creating hashTree..."<<"\n";
        pnode->setPath(current_directory);
        if(fs::is_regular_file(current_directory)){
            pnode->setIsFile(true); 
            pnode->setSignature(current_directory.string().c_str());
            return;
        }
        
        pnode->setIsFile(false);
        for(const auto &entry: fs::directory_iterator(current_directory)){
                HashNode *node= new HashNode();
                pnode->setNode(node);
                createTree(node,entry.path());
        }
        pnode->setSignature(current_directory.string().c_str());
    }

    /*
     print le tree avec un depth
    */
    void HashTree::printTree(HashNode* node, int depth) {
        if (!node) return;
    
        // Print indentation
        for (int i = 0; i < depth; i++) std::cout << "  ";
    
        // Print node type and signature
        if (node->getIsFile()) {
            std::cout << "[FILE] ";
        } else {
            std::cout << "[DIR]  ";
        }
        std::cout << "Signature: " << node->getSignature() << std::endl; 
        std::cout << "path: " << node->getPath() << std::endl; 
        for (HashNode* child : node->getNodeArray()) {
            printTree(child, depth + 1);
        }
    }
    
    
