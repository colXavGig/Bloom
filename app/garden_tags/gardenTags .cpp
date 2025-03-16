#include "gardenTags.h"
using namespace std;

class gardenTags{
    private:
        HashNode* roots;
    public:
        string note;

        gardenTags(HashNode* roots){
            setRoot(roots);
            setNote();
        };
        
    //setters
    void setRoot(HashNode* root){
        roots=root;
    }
    void setNote(){
        getline(cin,this->note); 
    }
    ostream& operator<<(std::ostream& os){
        cout<<"[root] "<<this->roots->getSignature()<<"\n"<<
             "[message] "<<this->note;
    }
};

