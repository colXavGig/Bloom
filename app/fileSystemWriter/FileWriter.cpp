#include "FileWriter.h"
#include <string.h>
#define LOGGER_STATUS LOGGER_ACTIVE
#include "../debugging.h"



using GP = gp::GardenProtocol;

/**
 *
 * @return return le hash du tag
 */
string fileWriter::writeToFile(HashTree *tree, string commit_msg, string parentsignature) {
    LOG(" ");
    LOG(" ");
    LOG("Starting to write tree to file...");
    this->createGarden(tree->getRoot());
    LOG("Garden seeds saved!");
    return this->savingGardenTag(tree, commit_msg, parentsignature);
}


void fileWriter::savingFile(const FileNode *node){
    
    //create fold
    fs::path path = gardenpath->getFlowerPath(node->getSignature());

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

    string folder,file;
    fs::path path = gardenpath->getFlowerPath(node->getSignature());

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
/**
 * patch retourne gardentag mais je pense pas que c'est trop bon
 * 
 * 
 */
string fileWriter::savingGardenTag(HashTree *tree, string tag_msg,string parentsignature ){
                                                                                            LOG("Saving garden tag...");
    GardenTag tag = GardenTag(tree, tag_msg, parentsignature);
                                                                                            LOG("Garden tag created!");
       
    //creation du path                                                                                     LOG("Garden seeds saved!");                                                                                       LOG(("Creating fs structure with hash: " + tag.getHash()).c_str());
    fs::path path = gardenpath->signaturePath(tag.getHash());                                                                                         LOG("FileStructure generated!"); 
    fs::path targetPath = this->gardenpath->getTagPath()/path;
                                                                                            LOG(("Making sure "+ targetPath.string() +" exists...").c_str());

    if (fs::exists(targetPath)) {
        LOG(("Tag already exists at: " + targetPath.string()).c_str());
        return tag.getHash();
    }
    fs::create_directories(targetPath.parent_path());
    std::ofstream outFile(targetPath);
    
    outFile <<GP::GardenEncode({"[PARENT]", tag.getparentSignature()})<<"\n";
    outFile <<GP::GardenEncode({"[MSG]",    tag.getMessage()})<<"\n";
    outFile <<GP::GardenEncode({"[TREE]",   tag.getRootHash()})<<"\n";
    outFile <<std::endl;

    outFile.close();
                                                                                            LOG(("root hash: "+tag.getHash()).c_str());
    return tag.getHash();
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

