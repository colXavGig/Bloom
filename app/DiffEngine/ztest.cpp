#include "TreeDiff.h"
#include <string>

#include "../fileSystemManagement/utilz/PathManagement/StaticPath.h"
using SP = staticpath::_staticPath;
using namespace std;

int main(int argc, char** argv){
    SP::SET(std::make_unique<GardenPath>("."));
    try{
        string headHash = "585adf0fc862d4992aab0091806043682aab07bf";    
        string targetHash = "ef4f6e1c7f588bc74a61682513fb3b08712cedcb";  

        TreeDiff diffEngine;
        diffEngine.compareTrees(headHash, targetHash);

        Diff& result = diffEngine.getDiff();

        if (result.hasConflicts()) {
            cout << "Merge conflicts detected!\n";
        } else {
            cout << "No conflicts.\n";
        }
        result.readAll(); 
    } catch (const std::exception& e) {
        cerr << "Fatal error: " << e.what() << std::endl;
    }


}