#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class FileBuilder {
    private:
        fs::path root;

    public:
        void setRoot(fs::path r){
            this->root=r;
        } 
        //constructeur
        FileBuilder(fs::path r){
            this->setRoot(r);
        }
        
        void buildfile(fs::path source,fs::path destination);
        void buildfolder(fs::path source,fs::path destination);
};