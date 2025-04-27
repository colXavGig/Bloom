#include "Index.h"
#include <fstream>
#include <cstring>
#include <vector>
#define LOGGING_STATUS LOGGER_INACTIVE
#include "../debugging.h"



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
  LOG("haloo");
  ofs << "[current] "<<value->current_branch->name<<" "<<value->current_branch->signature << std::endl;
  LOG("haloo");
  for (int i = 0; i < value->num_branches; i++) {
                                                                                    LOG("haloo");
    Branch& branch = value->branch_heads[i];
    ofs << branch.name <<" " << branch.signature <<" "<< std::endl;
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

  ifstream fis(path);
  if (fis.good()) {
                                                                              LOG("Successfully opened index file");
    string firstline, name;// premiere ligne est le current
    if (!fis.eof()) {                                                         
      getline(fis, firstline);
      char* c_line = &firstline[0];
      readToken(&c_line);//throw current
      name = readToken(&c_line);
    }
                                                                              LOG("Getting all branches...");
    std::string line, branch_name, signature; 
    while (getline(fis, line)) {
      char* c_line = &line[0];//maniere tres drole de faire un Char*
      branch_name = readToken(&c_line);
      signature   = readToken(&c_line);
                                                                              LOG(" ");
                                                                              LOG(("Branch name: " + branch_name).c_str());
                                                                              LOG(("Branch signature: " + signature).c_str());
                                                                              LOG(" ");                                                                                                                                                   
      addBranch(createBranch(branch_name, signature));  
                                                                              LOG("Branch added");
    }
    setCurrentBranch(name); 
  } else {  
                                                                              LOG("creating Index");
    addBranch(createBranch("main"," "));
    setCurrentBranch("main");
  }
  LOG("Closing index file...");
  fis.close();
  LOG("Successfully initialized index");
}
////////////////////////////////////////////
//          feature functions
///////////////////////////////////////////
void Index::commit(const string& signature){
  strcpy(value->current_branch->signature, signature.c_str());
}
string Index::getSignature(){
  return value->current_branch->signature;
}


void Index::setCurrentBranch(const string& name){ 
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
      if(name == value->branch_heads[i].name){
        throw std::invalid_argument("Branch name already exist");
      }
  }
  addBranch(createBranch(name,signature));
  LOG("print succesful.");
}


//////////////////////////////////////////
//         Helper functions
//////////////////////////////////////////

string Index::readToken(char **line) {
  string token;

  while (**line == ' ' || **line == '\n') {
      (*line)++;
  }
  while (**line != ' ' && **line != '\n' && **line != '\0') {   
     token += **line; 
     (*line)++;
  }
  return token; 
}

Branch* Index::createBranch(const std::string& branch_name, const std::string& signature) {
  Branch* branch = new Branch();
  branch->name = new char[branch_name.size() + 1];

  strcpy(branch->name, branch_name.c_str());
  strcpy(branch->signature, signature.c_str());

  return branch;
}