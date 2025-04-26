#include "Index.h"

#include <fstream>
#include <cstring>

#define LOGGING_STATUS LOGGING_ACTIVE
#include "../debugging.h"



//////////////////////////////////
//            PUBLIC            //
//////////////////////////////////

Index::Index(fs::path path) {
  LOG("Creating index...");
  this->path = path;
  init(path);
}

Index::~Index() {
  delete value;
}

string Index::getCurrentBranch() {
  return value->current_branch;
}

void Index::setCurrentBranch(string branch) {
  value->current_branch = new char[branch.size() + 1];
  strcpy(value->current_branch, branch.c_str());
}

void Index::addBranch(Branch *branch) {
  LOG("Adding branch called");
  LOG("Allocating memory");
  auto tmp = new Branch[++value->num_branches];

  LOG("Copying branches to the new memory");
  for (int i = 0; i < value->num_branches - 1; i++) {
    LOG("hallo");
    tmp[i] = value->branch_heads[i];
  }
  LOG("adding the new branch");
  tmp[value->num_branches - 1] = *branch;

  LOG("setting the buffer to the branch heads");
  value->branch_heads = tmp;
  LOG("branch added sucessfully");
}

Index_s *Index::getStructuralValue() {
  return value;
}

void Index::save() {
  std::ofstream ofs(path);
  ofs << "[current] " << value->current_branch << std::endl;
  for (int i = 0; i < value->num_branches; i++) {
    auto branch = value->branch_heads[i];
    ofs << "[" << branch.name << "] " << branch.signature << std::endl;
  }
  ofs.close();
}

Index::operator Index_s() {
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
    string firstLine;




    if (!fis.eof()) {
      LOG("Getting first line, the current branch.");
      getline(fis, firstLine);
      string currentBranch = firstLine.replace(0, 10, "");
      LOG(("Current branch is: " + currentBranch).c_str());
    }



    string line, branch_name, signature;
    LOG("Getting all branches...");


    
    while (!getline(fis, line).eof()) {
      int split = 0;
      for (int i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
          split = i;
          break;
        }
      }



      branch_name = line.substr(1, split - 2);
      signature = line.substr(split + 1);
      auto branch = new Branch;

      branch->name = branch_name.data();
      strcpy(branch->signature, signature.data());
      LOG(("Branch name: " + branch_name).c_str());
      addBranch(branch);
      LOG("Branch added");
    }




  } else {
    LOG("Failed to open index file");
    value->current_branch = "main";
    LOG("Current branch is: main" );
    auto branch = new Branch();
    LOG("setting up branch...");
    branch->name = new char[getCurrentBranch().size() + 1];
    strcpy(branch->name, getCurrentBranch().c_str());
    LOG("Adding current branch to branches...");
    addBranch(branch);

  }
  LOG("Closing index file...");
  fis.close();
  LOG("Successfully initialized index");
}

