#include "FileIterator.h"




FileIterator::FileIterator(std::string signature){
    ifs = new std::ifstream(this->path.getFlowerPath(signature).string());
    if (!ifs->is_open()) {
        ifs==NULL;
        std::cout<<"Warning ifs null\n";
    }

    Line = new line;  
    Line->index = 0; 
}


bool FileIterator::Next(){
    this->Line->index++;
    if (getline(*ifs, Line->buffer)) {
        Line->buffer.size() == 0 ? Line->buffer="\\n": Line->buffer;
        return true; 
    } else {
        Line->buffer="";
        return false;
    }
}


std::string FileIterator::getLine(){
    return this->Line->buffer;
}

int FileIterator::getIndex(){
    return this->Line->index;
}
