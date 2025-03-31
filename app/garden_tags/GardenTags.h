#include "../datacollection/hashTree/HashNode.h"
#include "../datacollection/hashTree/HashTree.h"
#include <iostream>
#include <string>
using namespace std;

class GardenTags{
    private:
        HashNode* roots;
    public:
        string note;
        GardenTags(HashNode* roots):roots(roots){};
        
    //setters
    void setRoot(HashNode root);
    void setNode();
    ostream& operator<<(std::ostream& os);
};