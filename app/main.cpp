#include "datacollection/hashTree/HashTree.h"
#include "fileWriter/FileWriter.h"
//#include "fileReader/component/Searcher.h"
#include "paths/GardenPath.h"
<<<<<<< HEAD
#include "algo/Compare/CompareTree.h"


=======
#include "fileReader/FileIterator.h"
#include "growth/Growth.h"

void commit(fileWriter paths, char** arr, int size);
//void search(char** arr, int size);
>>>>>>> 57c66847cdbd5f591c25e3e78601257cc47bbdde

int main(int argc, char** argv){
    auto paths = GardenPath(".");
    string cmd = (argc >= 1) ? argv[1] :/* === DEFAULT === */ "commit";
    if (cmd == "commit")
    {
        commit(&paths, argv +2, argc -2);
    } /*else if (cmd == "search")
    {
        search(argv+2, argc-2);
    }*/ else if (cmd == "comp"){
        cout<<"comparing"<<"\n";

<<<<<<< HEAD
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
=======
        FileIterator *it1 = new FileIterator("./app/testing/blob.txt");
        FileIterator *it2 = new FileIterator("./app/testing/blob2.txt");
        Growth g;
        while(it1->Next() | it2->Next()){
            g.compare(it1->getLine(),it1->getIndex(),it2->getLine(),it2->getIndex());
        }
        g.printChange();
>>>>>>> 57c66847cdbd5f591c25e3e78601257cc47bbdde
    }

    cout<<"succes";
    //getchar();
}

<<<<<<< HEAD
}


=======
void commit(GardenPath *paths, char** arr, int size)
{
    string tag_msg = (arr[0] == "-m") ? arr[1] : "";

    FolderNode *root = new FolderNode("./app/testing");
    HashTree HTree =  HashTree(root);

    fileWriter fw = fileWriter(paths);
    fw.writeToFile(&HTree, tag_msg);
}

/*
void search(char** arr, int size)
{
    Searcher s;
    s.rebuild("C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\.garden\\seeds\\2f\\a2f95fb5096f1c44b0a791b5d1c157fa5e614b.txt",
        "C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\ReaderTester");
}
*/
>>>>>>> 57c66847cdbd5f591c25e3e78601257cc47bbdde
