#include <stdio.h>
#include <string>
#include <vector>
/**
 * permet d'avoir la track la navigation
 * 
 * 
 */
class AnchorPath{
    private:
        std::vector<std::string> history;
        int size=-1;
    public:
        void forward(char *);
        void forward(std::string);
        void backward();
        void backward();
        std::string getPath();
        void setPath(char * str){
            forward(str);
            size ++;
        }
};