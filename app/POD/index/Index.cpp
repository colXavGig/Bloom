#include <cstring>
#include <vector>
#include "Index.h"

#define LOGGER_STATUS LOGGER_INACTIVE
#include "../../debugging.h"

//////////////////////////////////
//            PUBLIC            //
//////////////////////////////////

Index::Index() {
    index.current = nullptr;
    index.list = nullptr;

}

Index::~Index() {
   free_Index(&index);
}


Index_s *Index::getStructuralValue() {
    return &index;
}

void Index::save() {
    
    LOG(SP::_INDEX().string().c_str());
    std::ofstream ofs(SP::_INDEX().string());
    LOG((getCurrentName() + getTagHash()).c_str());
    ofs <<GP::GardenEncode({"[current]", getCurrentName(), getTagHash()}) << "\n";
    Branch *ptr = index.list;

    while(ptr){
        ofs <<GP::GardenEncode({string(ptr->name),string(ptr->hash)}) << "\n";
        ptr = ptr->next;
    }
    ofs.close();
}

Index::operator Index_s&() {
    return index;
}

Index::operator Index_s *() {
    return &index;
}

//////////////////////////////////
//            PRIVATE           //
//////////////////////////////////

bool Index::read() {
    LOG("Setting up index...");

    ifstream ifs(SP::_INDEX());

    if (ifs.good()) {
        std::string line; 
        getline(ifs,line); 
        vector<string> current =  GP::GardenDecode(line);                         
                                                                                            LOG("Successfully opened index file");                                                  
        while (std::getline(ifs, line)) {
            if(line.size()<=1)break;
                                                                                            LOG(("creating Index " +line).c_str());
            vector<string> vec = GP::GardenDecode(line);
            addBranch(vec[0], vec[1]);                  
                                                                                            LOG("added branch succesfully");                                                       
        }
        
        int err = set_current(&index,current[1].c_str());
        //TODO:: error handling
        if(err == 2) {
            throw runtime_error("current branch doesnt have a name FATAL ERROR");
        } 
        if(err == 3){
            defaultConfig();
        }
        ifs.close();
                                                                                            LOG(("index done"));
        return true;   
    } else {
        return false; 
    } 
}


void Index::init(const string& hash) {
    addBranch("main",hash);
    setCurrent("main");        
}

///////////////////////////////////////////
//          feature functions            //
///////////////////////////////////////////

void Index::updateHeadHash(const string& signature){
    strncpy(index.current->hash, signature.c_str(), 40);
    index.current->hash[40] = '\0';
}



void Index::setCurrent(const string& name){ 
    int err = set_current(&index,name.c_str());

    if(err == 2)
        printf("You need to enter a name to set a branch");
        
    if(err == 3)
        printf("Branch doesn't exist"); 

    return;  
}

void Index::plant(const string& branch_name){
    addBranch(branch_name, getTagHash());
};

void Index::ls(){
    Branch *ptr =index.list;
    while(ptr){
        printf("%s\t%s\n",ptr->name,ptr->hash);
        ptr = ptr->next;
    }
}
//////////////////////////////////////////
//         Helper functions
//////////////////////////////////////////

void Index::addBranch(const std::string& name, const std::string& hash) {
        LOG((name +"\t"+hash+"\n").c_str());
        int error = add_branch(&index,name.c_str(), hash.c_str());
        if(error == 2){
            throw bad_alloc() ;
        }
        
        if(error == 3) 
            printf("Index::setBranch: couldn't add branch internal error");
}

string Index::getTagHash(){
    return index.current->hash;
}
string Index::getCurrentName(){
    return index.current->name;
}

void Index::defaultConfig(){
    int err = set_current(&index,"main");
    if(err == 2)
        throw logic_error("Index_c_api::set_current error in param ");

    if(err == 3){
        throw runtime_error("FATAL ERROR: main doesn't exist TODO create protocol to adresse error");
    }
}


