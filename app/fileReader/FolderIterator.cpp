#include "FolderIterator.h"


FolderIterator::FolderIterator(std::string signature){
    ifs = new std::ifstream(this->path.getFlowerPath(signature).string());
    if (!ifs->is_open()) {
        std::cout<<"Warning null stream\n";
        ifs = NULL;
    } 
}



bool FolderIterator::Next(){
    std::string buffer;
    this->token="";
    this->signature="";
    this->filename="";
    if (getline(*ifs, buffer)) {
        int i=0;
        //std::cout<<"buffer: "<<buffer<<"\n";
        while(i < buffer.length() && buffer[i] != ' ') this->token+=buffer[i++];
        i++;
        while(i < buffer.length() && buffer[i] != ' ') this->signature+=buffer[i++];      
        i++;
        while(i < buffer.length()) this->filename+=buffer[i++];
      
        return true; 
    } else {
        return false;
    }
};


std::string FolderIterator::getToken(){
    return this->token;
}

std::string FolderIterator::getSignature(){
    return this->signature;
}

std::string FolderIterator::getFilename(){
    return this->filename;
}