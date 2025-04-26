#include "AnchorPath.h"

void AnchorPath::forward(char * str){
    history.push_back(str);
    size++;
}
void AnchorPath::forward(std::string str){
    history.push_back(str);
    size++;
}
void AnchorPath::backward(){
    size--;
}
void AnchorPath::backward(){
    size--;
}
std::string AnchorPath::getPath(){
    return  history[size];
}