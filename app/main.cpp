#include "dataCollection/HashTree/HashTree.h"
#include "fileWriter/fileWriter.h"
#include "fileReader/component/Searcher.h"
int main(){
//     FolderNode *root = new FolderNode(
//         "C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\testing");
//     HashTree HTree =  HashTree(root);

   

//    fileWriter fw = fileWriter(
//         "C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\.garden\\seeds");
//     fw.createGarden(HTree.getRoot());
//     cout<<"succes";
//     getchar();
    Searcher s;
    s.rebuild("C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\.garden\\seeds\\2f\\a2f95fb5096f1c44b0a791b5d1c157fa5e614b.txt",
        "C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\ReaderTester");
        cout<<"succes";
        getchar();
}