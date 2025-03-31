#include <iostream>
#include <filesystem>
#include <fstream>
#include "FileBuilder.h"
#include "../datacollection/hashTree/HashNode.h"
using namespace std;
namespace fs = std::filesystem;

/*
 un iterator qui navigue les info des file du garden
 il ne les lit pas il ne fait que les naviguer
 
*/
enum content_token{
    FOLDERS,
    FILES,
    INCOMPATIBLE,
};

class Searcher{
    private:
        const fs::path gardenPath = fs::current_path()/=".garden\\seeds";
        //for testing has to be changed
        
        //void process(content_token token, string line, fs::path path);
        void dispatchFileBuilder();

    public:
        fs::path findpath(string hash);
        void rebuild(fs::path rootNode, fs::path rootFolder);
        void gotoFile(); 
        void openFolderIterator();
        void openFileIterator();

};

