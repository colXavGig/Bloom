#pragma once

#include <string>

#include "Index_struct.h"

using namespace std;


class Index {
    public:
        Index();
        ~Index();

        string getCurrentBranch();
        void setCurrentBranch(string branch);

        Index_s *getStructuralValue();
        operator Index_s();
        operator Index_s *();
    private:
        Index_s *value;

        void init();



};



