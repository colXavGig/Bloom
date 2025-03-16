#include "fileWriter.h"


void fileWriter::createFileStructure(const HashNode &node,string &foldername,string &filename){
    string fullsignature=node.getSignature();
    for(size_t i=0;i<fullsignature.size();i++){
        (i<2) ? foldername += fullsignature[i] : filename += fullsignature[i];
    }
    filename += node.getPath().extension().string();
}

void fileWriter::fileToGarden(const HashNode &node){
    string foldername,filename;
    fs::path temp_path=gardenpath;
    createFileStructure(node,foldername,filename);
    temp_path/=foldername;
    fs::create_directories(temp_path);
    if(!fs::exists(temp_path/=filename))
        fs::copy(node.getPath(),temp_path);  
}
//convertit en txt pour l'instant jsp c quoi le meilleur ouvert a des propositions
// example : 
// folder :
// [currentdirname]
//    root_dir 
//   [ type ]  [ hash ]   [ filename ]
//     file    aexvvsdfa   file1.txt
//     file    sadfsadff   file2.txt
//     Folder  asdfhsdfs   subdir
void fileWriter::FolderToFile(const HashNode &file, string filename){
    ifstream check(filename+=".txt");

    if(check)return;// si fichier existe pas de overwrite  

    ofstream ofs(filename+=".txt");
    ofs<<file.getPath().filename()<<"\n";
    for(HashNode *node : file.getNodeArray()){
        ofs<<((node->getIsFile()) ? "FILE" : "FOLDER")<<" " 
        << node->getSignature()<<" "<<node->getPath().filename() <<"\n";
    }
}

void fileWriter::folderToGarden(const HashNode &node){
    string foldername,filename;
    createFileStructure(node,foldername,filename);
    fs::path temp_path=gardenpath;
    temp_path/=foldername;
    fs::create_directories(temp_path);
    FolderToFile(node,(temp_path/=filename).string());
   
}

void fileWriter::CreateGarden(HashNode current){
    if(current.getIsFile()){
        cout<<"doing a file\n";
        fileToGarden(current);
        return;
    } else {
        cout<<"doing a folder\n";
        for(HashNode *HNode : current.getNodeArray()){
           CreateGarden(*HNode);
        }
        folderToGarden(current);
    }   
};

