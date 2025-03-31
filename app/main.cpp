#include "datacollection/hashTree/HashTree.h"
#include "fileWriter/FileWriter.h"
//#include "fileReader/component/Searcher.h"
#include "paths/GardenPath.h"
#include "fileReader/FileIterator.h"
#include "growth/Growth.h"
int main(int argc, char** argv){
    auto paths = GardenPath(".");
    string cmd = (argc >= 1) ? argv[1] :/* === DEFAULT === */ "commit";
    if (cmd == "commit")
    {
        FolderNode *root = new FolderNode("./app/testing");
        HashTree HTree =  HashTree(root);

        fileWriter fw = fileWriter(paths.getGardenPath());
        fw.createGarden(HTree.getRoot());
     
    } else if (cmd == "search")
    {
            //Searcher s;
            
           // s.rebuild("C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\.garden\\seeds\\2f\\a2f95fb5096f1c44b0a791b5d1c157fa5e614b.txt",
            //   "C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\ReaderTester");
    }  else if (cmd == "comp"){
        cout<<"comparing"<<"\n";
        
        FileIterator *it1 = new FileIterator("./app/testing/blob.txt");
        FileIterator *it2 = new FileIterator("./app/testing/blob2.txt");
        Growth g;
        while(it1->Next() | it2->Next()){
           g.compare(it1->getLine(),it1->getIndex(),it2->getLine(),it2->getIndex());
        }
        g.printChange();
    }

    cout<<"succes";
    //getchar();

}