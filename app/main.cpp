#include "dataCollection/HashTree/HashTree.h"
#include "fileWriter/fileWriter.h"

int main(){
    FolderNode *root = new FolderNode(
        "C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\testing");
    HashTree HTree =  HashTree(root);

    fileWriter fw = fileWriter(
        "C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\.garden\\seeds");
    fw.createGarden(HTree.getRoot());
    cout<<"succes";
    getchar();
}