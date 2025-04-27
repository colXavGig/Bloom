#include "FileWriter.h"
#include <string.h>
#define LOGGER_STATUS LOGGER_ACTIVE
#include "../debugging.h"


/**
 * 
 * 
 * 
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

void fileWriter::createFileStructure(string fullsignature,string &folder,string &file){  
    for(size_t i=0;i<fullsignature.size();i++){
        (i<2) ? folder += fullsignature[i] : file += fullsignature[i];
    }
}

void fileWriter::savingFile(const FileNode *node){
    //initialise path;
    fs::path temp_path = gardenpath->getSeedPath();
    //create fold
    string folder, file;

    createFileStructure(node->getSignature(),folder,file);

    temp_path/=folder;

    fs::create_directories(temp_path);

    if(!fs::exists(temp_path/=file)){
        fs::copy(node->getPath(),temp_path);
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
    createFileStructure(node->getSignature(),folder,file);

    fs::path temp_path = gardenpath->getSeedPath();

    fs::create_directories(temp_path/=folder);
    
    ifstream check( temp_path/=file+=".txt");
    if(check)return;
    ofstream ofs(temp_path);

    //writing to folder file
    ofs<<"[FOLDERNAME]"<<" "<<node->getFileName()<<"\n";
    for(FileNode *file : node->getFiles()){
        ofs<<"[FILE]"<<" "<<file->getSignature()<<" "<<file->getFileName()<<"\n";
    }
    for(FolderNode *folder : node->getFolders()){
        ofs<<"[FOLDER]"<<" "<<folder->getSignature()<<" "<<folder->getFileName()<<"\n";
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
    string folderPath, filePath;
                                                                                            LOG("Garden seeds saved!");
                                                                                            LOG(("Creating fs structure with hash: " + tag.getHash()).c_str());
    createFileStructure(tag.getHash(), folderPath, filePath);
                                                                                            LOG("FileStructure generated!");
                                                                                            LOG(("Folder path: "+folderPath).c_str());
                                                                                            LOG(("File path: "+filePath).c_str());
    fs::path targetPath = this->gardenpath->getTagPath();
    fs::create_directory(targetPath);                                                       LOG(("Making sure "+ targetPath.string() +" exists...").c_str());
    targetPath/= folderPath;
    fs::create_directory(targetPath);                                                       LOG(("Making sure "+ targetPath.string() +" exists...").c_str());
    targetPath /= filePath;
     if (fs::exists(targetPath)) {
         LOG(("Tag already exists at: " + targetPath.string()).c_str());
         return tag.getHash();
    }
    std::ofstream outFile(targetPath);
    
    outFile << "[PARENT] "<<tag.getparentSignature()<< std::endl;
    outFile << "[MSG] " << tag.getMessage() << std::endl;
    outFile << "[TREE] " << tag.getRootHash() << std::endl;
    outFile <<  std::endl;

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

