#include "HashTree.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <filesystem>
#include <direct.h>
#include <openssl/sha.h>
namespace std{

    void tree::setHash(const string& str) override {
        unsigned char hashlenght[SHA_DIGEST_LENGH];
        hash=SHA1(str, sizeof(str), hashlenght);
    }

    void flower::setHash() override {

    }    
    



void HashTree::getCurrentDirectory(){
    char cwd[_MAX_PATH];
    if(_getcwd(cwd, sizeof(cwd) != NULL){
        current_directory = cwd;
    } else {
        cerr << "Unable to get directory";
    }
}
};