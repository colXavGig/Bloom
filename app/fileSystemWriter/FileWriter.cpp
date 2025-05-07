#include "FileWriter.h"
#include <string.h>
#define LOGGER_STATUS LOGGER_INACTIVE
#include "../debugging.h"



using GP = gp::GardenProtocol;

string fileWriter::init(HashTree *tree, string commit_msg, Index *index) {    
    //TODO create a class to manage commits and rollback 
    //TODO creation de bon message d'erreur
    // :: si c'est deja init couper operation que rien seras enregistrer (pour l'instant rien s'enregistre)
    try {
        
        GardenTag tag = GardenTag(tree->getRoot()->getSignature(),commit_msg,"FIRST");

        tag.write();
        cout<<"hello "<<tag.getTagHash();
        index->init(tag.getTagHash());

        createGarden(tree->getRoot());    
    } catch(const exception& e) {
        cerr<< e.what();
        return"";
    }
    return "succes";
}


string fileWriter::commit(HashTree *tree, string commit_msg, Index *index) {
    
    //TODO create a class to manage commits and rollback 
    //TODO creation de bon message d'erreur
    // :: si le commit precedent a le meme hash avertir que rien seras enregistrer (pour l'instant rien s'enregistre)
    try {
        cout<<tree->getRoot()->getSignature()+"\n";
        GardenTag tag = GardenTag(tree->getRoot()->getSignature(),commit_msg,index->getTagHash());

        tag.write();
     
        createGarden(tree->getRoot());

        index->updateHeadHash(tag.getTagHash());
    } catch(const exception& e) {
        cerr<< e.what();
        return"";
    }
    return "succes";
}
void fileWriter::createGarden(FolderNode *current){

    for(FileNode* node : current->getFiles()){
        savingFile(node);
    }
    for(FolderNode* node : current->getFolders()){
        createGarden(node);
    }
    savingFolder(current);
}   

void fileWriter::savingFile(const FileNode *node){
    
    //create fold
    fs::path path =SP::_SEEDROOT(node->getSignature());

    fs::create_directories(path.parent_path());
    if(!fs::exists(path)){
        fs::copy(node->getPath(),path);
    }

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

    fs::path path = SP::_SEEDROOT(node->getSignature());

    fs::create_directories(path.parent_path());
    ofstream ofs(path);
    //writing to folder file
    ofs << GP::GardenEncode({"[FOLDERNAME]",node->getFileName()}) << "\n";
    for(FileNode *file : node->getFiles()){
        ofs<< GP::GardenEncode({"[FILE]",file->getSignature(),file->getFileName()})<<"\n";
    }
    for(FolderNode *folder : node->getFolders()){
        ofs<< GP::GardenEncode({"[FOLDER]",folder->getSignature(),folder->getFileName()})<<"\n";
    }
}




