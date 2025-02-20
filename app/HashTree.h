#include <filesystem>
#include <Windows.h>
#include <string>
#include <vector>
namespace std{
class Node {
    protected:
        string hash;
        filesystem::path path;
        bool is_directory;
        vector<Node*> node_List;
    public:
        virtual void setHash();
};


class HashTree{
    protected:
        string hash;
        vector<Node*> node_List;
        string current_directory;
    void createIterator(this);

    public:
    HashTree():{

    }
    addNode(){
        node_List.put_back()
    }
    
}

}