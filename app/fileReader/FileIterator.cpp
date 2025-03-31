#include "FileIterator.h"


bool FileIterator::Next(){
    this->Line->index++;
    return readline();
}

bool FileIterator::readline(){
        if (getline(*ifs, Line->buffer)) {
            Line->buffer.size() == 0 ? Line->buffer="\\n": Line->buffer;//need to put \n
            return true; 
        } else {
            Line->buffer="";
            return false;
        }
}


string FileIterator::getLine(){
    return this->Line->buffer;
}

int FileIterator::getIndex(){
    return this->Line->index;
}
