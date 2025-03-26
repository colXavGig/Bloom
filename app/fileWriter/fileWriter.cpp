#include "FileWriter.h"


void fileWriter::createFileStructure(string fullsignature,string &folder,string &file){  
    for(size_t i=0;i<fullsignature.size();i++){
        (i<2) ? folder += fullsignature[i] : file += fullsignature[i];
    }
    
}
void fileWriter::savingFile(const FileNode *node){
    cout<<"FILE\n";
    //initialise path;
    fs::path temp_path=gardenpath;
    //create fold
    string folder,file;
    cout<<"\tsignature "<<node->getSignature()<<"\n";
    createFileStructure(node->getSignature(),folder,file);
    cout<<"\tfolder: "<<folder<<"\n";
    cout<<"\tfile: "<<file<<"\n";
    temp_path/=folder;

    fs::create_directories(temp_path);
    if(!fs::exists(temp_path/=file)){
        fs::copy(node->getPath(),temp_path);}

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
void fileWriter::savingFolder(const FolderNode *node){
    cout<<"FOLDER\n";
    string folder,file;
    cout<<"\tsignature "<<node->getSignature()<<"\n";
    createFileStructure(node->getSignature(),folder,file);
    cout<<"\tfolder: "<<folder<<"\n";
    cout<<"\tfile: "<<file<<"\n";
    fs::path temp_path=gardenpath;

    fs::create_directories(temp_path/=folder);
    
    ifstream check( temp_path/=file+=".txt");
    if(check)return;
    ofstream ofs(temp_path);

    //writing to folder file
    ofs<<"[FOLDERNAME]"<<node->getFileName()<<"\n";
    for(FileNode *file : node->getFiles()){
        ofs<<"[FILE]"<<" "<<file->getSignature()<<" "<<file->getFileName()<<"\n";
    }
    for(FolderNode *folder : node->getFolders()){
        ofs<<"[FOLDER]"<<" "<<folder->getSignature()<<" "<<folder->getFileName()<<"\n";
    }
}


void fileWriter::createGarden(FolderNode *current){
    cout<<"about to save seeds\n";
    for(FileNode* node : current->getFiles()){
        savingFile(node);
    }
    for(FolderNode* node : current->getFolders()){
        createGarden(node);
    }
    savingFolder(current);
}   

