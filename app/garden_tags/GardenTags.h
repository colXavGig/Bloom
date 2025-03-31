#include "../datacollection/hashTree/HashNode.h"
#include "../datacollection/hashTree/HashTree.h"
#include <iostream>
#include <string>
using namespace std;

class GardenTags{
    private:
        FolderNode* roots;
    public:
        string note;
        GardenTags(FolderNode* roots):roots(roots){};
        
    //setters
    void setRoot(FolderNode root);
    void setNode();

    //getters
    FolderNode* getRoot(){
        return this->roots;
    }
    ostream& operator<<(std::ostream& os);
};