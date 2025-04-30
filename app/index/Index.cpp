#include "Index.h"
#include <cstring>
#include <vector>
#define LOGGING_STATUS LOGGER_INACTIVE
#include "../debugging.h"
using GP = gp::GardenProtocol;



//////////////////////////////////
//            PUBLIC            //
//////////////////////////////////

Index::Index(const fs::path& p): path(p) {
    LOG("Creating index...");
    init(path);
}

Index::~Index() {
    if (value) {
        if (value->branch_heads) {
            for (int i = 0; i < value->num_branches; ++i) {
                delete[] value->branch_heads[i].name; 
            }
        delete[] value->branch_heads; 
        }
        delete value; 
    }
}


void Index::addBranch(Branch *branch) {
                                                                              LOG(" ");
                                                                              LOG("Allocating temp branch + 1");
    auto tmp = new Branch[++value->num_branches]; 
                                                                              LOG("Copying branches to temp");                                                                          
    for (int i = 0; i < value->num_branches-1; i++) {
        tmp[i] = value->branch_heads[i];                                                                            
    }
                                                                              LOG("adding the new branch");
    tmp[value->num_branches - 1].name = new char[strlen(branch->name) + 1];                                                                            
    strcpy(tmp[value->num_branches - 1].name, branch->name);
    strcpy(tmp[value->num_branches - 1].signature, branch->signature);
                                                                              LOG("setting the buffer to the branch heads");
    delete[] value->branch_heads;
    value->branch_heads = tmp;
                                                                              LOG("branch added sucessfully");
                                                                              LOG(" ");
}

Index_s *Index::getStructuralValue() {
    return value;
}

void Index::save() {
    std::ofstream ofs(path);

    ofs <<GP::GardenEncode({"[current]", getName(), getHash()}) << "\n";

    for (int i = 0; i < value->num_branches; i++) {
        ofs <<GP::GardenEncode({getBranchName(i),getBranchHash(i)}) << "\n";
    }
    ofs.close();
}

Index::operator Index_s&() {
    return *value;
}

Index::operator Index_s *() {
    return value;
}

//////////////////////////////////
//            PRIVATE           //
//////////////////////////////////

void Index::init(fs::path path) {
  LOG("Setting up index...");
  value = new Index_s();

  ifstream ifs(path);
    if (ifs.good()) {
        vector<string> firstrow = setCurrentBranch(ifs);                           
        LOG("Successfully opened index file");
        if(firstrow.size()<2){
            throw runtime_error("Index::Init : firstrow has to be atleast 2 data");
        }
                                                                             
        std::string line; 
        while (std::getline(ifs, line)) {
            LOG(("line "+line).c_str());
            vector<string> vec = GP::GardenDecode(line);
            if(vec.size()<2){
                throw runtime_error("Index::Init : rows has to be atleast 2 data");
            }

            LOG(("name " + vec[0] + " hash "+ vec[1]).c_str());                                                                                                                                                                                                                    
            addBranch(createBranch(vec[0], vec[1]));                                                                         
        }
        changeBranch(firstrow[1]); 
    } else {  
                                                                              LOG("creating Index");
        addBranch(createBranch("main"," "));
        changeBranch("main");
    }
    ifs.close();
}




////////////////////////////////////////////
//          feature functions
///////////////////////////////////////////
void Index::commit(const string& signature){
    strcpy(value->current_branch->signature, signature.c_str());
}



void Index::changeBranch(const string& name){ 
    for(int i=0; i < value->num_branches; i++){
        if(strcmp(name.c_str(), value->branch_heads[i].name) == 0){
            value->current_branch = &value->branch_heads[i];
            return;
        }
    }
    throw std::invalid_argument("no name exist");
}


void Index::createNewBranch(const string& name,const string& signature){
    for(int i=0; i < value->num_branches; i++){
        if(strcmp(name.c_str(), value->branch_heads[i].name) == 0){
            throw std::invalid_argument("Branch name already exist");
        }
    }
    LOG(name.c_str());
    addBranch(createBranch(name,signature));
    LOG("print succesful.");
}


//////////////////////////////////////////
//         Helper functions
//////////////////////////////////////////

Branch* Index::createBranch(const std::string& branch_name, const std::string& signature) {
    Branch* branch = new Branch();
    branch->name = new char[branch_name.size() + 1];

    strcpy(branch->name, branch_name.c_str());
    strcpy(branch->signature, signature.c_str());

    return branch;
}

vector<string> Index::setCurrentBranch(ifstream &ifs){
    string line;                                                      
    getline(ifs, line);
    return GP::GardenDecode(line); 
}

string Index::getHash(){
    return value->current_branch->signature;
}
string Index::getName(){
    return value->current_branch->name;
}


string Index::getBranchHash(int x){
    if(x>value->num_branches) throw out_of_range("getBranchHash: index out of range");
    return value->branch_heads[x].signature;
}

string Index::getBranchName(int x){
    if(x>value->num_branches) throw out_of_range("getBranchName: index out of range");
    return value->branch_heads[x].name;
}