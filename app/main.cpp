#include "dataCollection/HashTree/HashTree.h"
#include "fileWriter/fileWriter.h"

int main(){
    
    HashTree HTree =  HashTree(
        "C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\testing");

    fileWriter fw = fileWriter(
        "C:\\Users\\willd\\OneDrive\\Desktop\\projet structure\\Bloom\\app\\.garden\\seeds");
    fw.CreateGarden(*HTree.getRoot());
    cout<<"succes";
    getchar();
}