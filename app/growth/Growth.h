#include<iostream>
#include <vector>
using namespace std;

class Growth{
    private:
        vector<string> change;
    public:
        void compare(string line1,int indexline1,string line2,int indexline2);
           

        void printChange();
};
