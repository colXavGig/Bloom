#include <iostream>
#include <filesystem>
#include <fstream>
#include "FileBuilder.h"
using namespace std;
namespace fs = std::filesystem;
/* un iterator qui navigue les information requise
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
        fs::path root = 
        "C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\ReaderTester";
        void process(content_token token, string line, fs::path path);
        void dispatchFileBuilder();

    public:
        fs::path findpath(string hash);
        void rebuild(fs::path rootNode, fs::path rootFolder);
        

};

