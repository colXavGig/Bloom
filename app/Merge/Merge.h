#include "../fileSystemManagement/garden_tags/GardenTag.h"
#include "../algo/Diff.h"


class Merge{
    public:
        Merge(GardenTag head, GardenTag target);
       ~Merge();


    private:
        Diff head;
        Diff target; 
        GardenTag base;

        GardenTag findBase(const GardenTag& head,const  GardenTag& target);
};