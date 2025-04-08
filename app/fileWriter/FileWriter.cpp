#include "FileWriter.h"

#include "../garden_tags/GardenTag.h"

#define LOGGER_STATUS LOGGER_INACTIVE
#include "../debugging.h"

void fileWriter::writeToFile(HashTree *tree, string commit_msg) {
    LOG("Starting to write tree to file...");
    this->createGarden(tree->getRoot());
    LOG("Garden seeds saved!");
    this->savingGardenTag(tree, commit_msg);
    LOG("Garden tags saved!");
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
    ofs<<"[FOLDERNAME]"<<node->getFileName()<<"\n";
    for(FileNode *file : node->getFiles()){
        ofs<<"[FILE]"<<" "<<file->getSignature()<<" "<<file->getFileName()<<"\n";
    }
    for(FolderNode *folder : node->getFolders()){
        ofs<<"[FOLDER]"<<" "<<folder->getSignature()<<" "<<folder->getFileName()<<"\n";
    }
}

void fileWriter::savingGardenTag(HashTree *tree, string tag_msg){
    LOG("Saving garden tag...");
    GardenTag tag = GardenTag(tree, tag_msg);
    LOG("Garden tag created!");
    string folderPath, filePath;
    LOG("Garden seeds saved!");
    LOG(("Creating fs structure with hash: " + tag.getHash()).c_str());
    createFileStructure(tag.getHash(), folderPath, filePath);
    LOG("FileStructure generated!");
    LOG(("Folder path: "+folderPath).c_str());
    LOG(("File path: "+filePath).c_str());
    fs::path targetPath = this->gardenpath->getTagPath();
    fs::create_directory(targetPath); LOG(("Making sure "+ targetPath.string() +" exists...").c_str());
    targetPath/= folderPath;
    fs::create_directory(targetPath); LOG(("Making sure "+ targetPath.string() +" exists...").c_str());
    targetPath /= filePath;
    std::ofstream outFile(targetPath);

    outFile << "[MSG] " << tag.getMessage() << std::endl;
    outFile << "[TREE] " << tag.getRootHash() << std::endl;
    outFile <<  std::endl;

    outFile.close();
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

