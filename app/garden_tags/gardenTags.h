#include "../datacollection/hashTree/HashNode.h"
#include "../datacollection/hashTree/HashTree.h"
#include <iostream>
#include <string>
using namespace std;

class gardenTags{
    private:
        HashNode* roots;
    public:
        string note;
        gardenTags(HashNode* roots):roots(roots){};
        
    //setters
    void setRoot(HashNode root);
    void setNode();
    ostream& operator<<(std::ostream& os){
        cout<<"[root] "<<this->roots->getSignature()<<"\n"<<
             "[message] "<<this->note;
    }
};