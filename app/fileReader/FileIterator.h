#include <iostream>
#include <fstream>

using namespace std;

struct line{
    string buffer;
    int index;
};

class FileIterator {
    private:
        ifstream *ifs; 
        line *Line;
        bool readline();
    public:
        bool Next();
        FileIterator(string path){
            ifs = new ifstream(path);
            if (!ifs->is_open()) {
                cout << "Failed to open file: " << path << endl;
                throw std::runtime_error("Failed to open file.");
            }
    
            Line = new line;  
            Line->index = 0;  
            
        }

        string getLine();

        int getIndex();
};