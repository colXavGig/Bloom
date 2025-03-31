#include "datacollection/hashTree/HashTree.h"
#include "fileWriter/FileWriter.h"
#include "fileReader/component/Searcher.h"
#include "paths/GardenPath.h"

int main(int __argc, char** __argv){
    auto paths = GardenPath(".");
    auto cmd = (__argc > 1) ? __argv[1] :/* === DEFAULT === */ "commit";
    if (cmd == "commit")
    {
        FolderNode *root = new FolderNode("./app/testing");
        HashTree HTree =  HashTree(root);


        fileWriter fw = fileWriter(paths.getGardenPath());
        fw.createGarden(HTree.getRoot());
     
    } else if (cmd == "search")
    {
            Searcher s;
            
            s.rebuild("C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\.garden\\seeds\\2f\\a2f95fb5096f1c44b0a791b5d1c157fa5e614b.txt",
                "C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\ReaderTester");
    }

    cout<<"succes";
    //getchar();

}