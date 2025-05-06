#include "Merge.h"
#include <unordered_set>

Merge::Merge(GardenTag head, GardenTag target) {
    base = findBase(head, target);
}


Merge::~Merge(){

}

GardenTag Merge::findBase(const GardenTag& head,const  GardenTag& target){
    std::unordered_set<std::string> historique;

    GardenTag walker = head;
    while(walker.getMessage()=="FIRST"){
        std::string parent_hash = walker.getParentHash();
        historique.insert(parent_hash);
        walker = GardenTag(parent_hash);
    }
    walker = target;
    while (!walker.getParentHash().empty()) {
        std::string parent_hash = walker.getParentHash();
        if (historique.count(parent_hash)) {
            return GardenTag(parent_hash); 
        }
        walker = GardenTag(parent_hash);
    }
    throw std::runtime_error("No common ancestor found");
}
