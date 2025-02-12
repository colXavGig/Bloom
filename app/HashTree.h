#include <stdio.h>
#include <string>
#include <vector>
namespace std{
class Node {
    protected:
        string hash;

    public:
        virtual void setHash();
};

class tree : public Node {
    private:
        vector<Node*> node_List;

    public:
        void setHash()override;
};

class flower : public Node {
    private:

    public:
        void setHash()override;
};

class HashTree{
    protected:
        string hash;
        vector<Node*> node_List;
        string current_directory;
    void createIterator(this);

    public:
    void getCurrentDirectory();
}

}