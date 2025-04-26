#include <stdio.h>
#include "FOS/FILE_S.h"
#include <new>  


class Diff{
    private:
        FILE_S *diff;
        size_t size;
        size_t capacity;
    public:
        Diff():size(0), capacity(5){ diff = (FILE_S*)malloc(capacity * sizeof(FILE_S));}

        void add(FILE_S *f);//file is in the heap

        bool tryRead(FILE_S out);
};