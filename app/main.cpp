#include "datacollection/hashTree/HashTree.h"
#include "fileWriter/FileWriter.h"
#include "paths/GardenPath.h"
#include "algo/Juxtapose.h"
#include <iostream>
void commit(GardenPath *paths, char** arr, int size);
//void search(char** arr, int size);

int main(int argc, char** argv){
    GardenPath paths = GardenPath(".");
    string cmd = (argc > 1) ? argv[1] :/* === DEFAULT === */ "commit";
    if (cmd == "commit")
    {
        commit(&paths, argv +2, argc -2);
    } else if (cmd == "comp"){

        Juxtapose diff;
        try{
            diff.parseMetadata("0a5c758ae3608bd5a2a3a8750409256cbc5e2ff2.txt",
                               "0a5c758ae3608bd5a2a3a8750409256cbc5e2ff2.txt","myLOOOOOOVE");
        } catch(const runtime_error &err){
           cerr<< err.what();
        }
        
    cout<<"succes";
    } else if (cmd == "growback"){
     
    cout<<"succes";


    }


}

void commit(GardenPath *paths, char** arr, int size)
{
    string tag_msg = (arr[0] == "-m") ? arr[1] : "<EMPTY>";

    FolderNode *root = new FolderNode("./app/testing");
    HashTree HTree =  HashTree(root);
    fileWriter fw = fileWriter(paths);
    fw.writeToFile(&HTree, tag_msg);
}


// void Diff(FOS *fos,const fs::path &p1,const fs::path &p2){
//     Juxtapose diff;
//     //checks
//     if(fs::exists(p1) && fs::exists(p2)) 
//         throw new runtime_error("Path invalide.");    

//     if(fs::status(p1).type() != fs::status(p2).type())
//         throw std::runtime_error("Paths sont des different type");

//     if(fs::is_directory(p1)){
//         diff.folder(fos, p1.string().c_str(), p1.string().c_str());
//     }
//     if(fs::is_regular_file(p1)){
//         diff.file(fos, p1.string().c_str(), p1.string().c_str());
//     }
// }
/*
void search(char** arr, int size)
{
    Searcher s;
    s.rebuild("C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\.garden\\seeds\\2f\\a2f95fb5096f1c44b0a791b5d1c157fa5e614b.txt",
        "C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\ReaderTester");
}
*/

