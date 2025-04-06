#include "datacollection/hashTree/HashTree.h"
#include "fileWriter/FileWriter.h"
//#include "fileReader/component/Searcher.h"
#include "paths/GardenPath.h"
#include "algo/Compare/CompareTree.h"



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

        CompareTree comp;
        //remplacer ca par des commits
        comp.compareFolder("80c0b919e881434f1e18fc097bc79033014e31eb.txt","0a5c758ae3608bd5a2a3a8750409256cbc5e2ff2.txt");
        comp.printChange();
    cout<<"succes";
    } else if (cmd == "growback"){
        cout<<"comparing"<<"\n";

        CompareTree comp;
        //remplacer ca par des commits
        comp.compareFolder("80c0b919e881434f1e18fc097bc79033014e31eb.txt","0a5c758ae3608bd5a2a3a8750409256cbc5e2ff2.txt");
        comp.printChange();
    cout<<"succes";
    }

    cout<<"succes";
    //getchar();

}


