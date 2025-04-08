#include "Index.h"

#include <cstring>



//////////////////////////////////
//            PUBLIC            //
//////////////////////////////////

Index::Index() {
    value = new Index_s;
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

Index_s *Index::getStructuralValue() {
  return value;
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

void Index::init() {
  value = new Index_s;
}