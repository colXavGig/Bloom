#include "HashTree.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <filesystem>
#include <openssl/sha.h>

namespace std{
    void HashTree::getCurrentDirectory(){
        char cwd[_MAX_PATH];
        if(_getcwd(cwd, sizeof(cwd) != NULL){
            current_directory = cwd;
        } else {
        cerr << "Unable to get directory";
        }
    }

    
};