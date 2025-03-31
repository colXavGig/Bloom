#include "Growth.h"


void Growth::compare(string line1,int indexline1,string line2,int indexline2){
    if(line1 == line2) return;
    change.push_back(to_string(indexline1) + " [-] "+((line1.size()==NULL) ? " ":line1) + "\n"
                   + to_string(indexline2) + " [+] "+((line2.size()==NULL) ? " ":line2) + "\n");
};

void Growth::printChange(){
    for(string l : change){
        cout<< l<<"\n";
    }
}