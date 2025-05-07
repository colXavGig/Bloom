#include "Juxtapose.h"
using namespace std;


void Juxtapose::parseMetadata(const char *sign1, const char *sign2, string p){
    //li le folder file et sort les folders et files
    std::string p1 =SP::_SEEDROOT(sign1).string();
    std::string p2 =SP::_SEEDROOT(sign2).string();




    parsefile(p);
    parsefolder(p);
}

void Juxtapose::loadBlocks(const char* signature, vector<Block>& blockList) {
    ifstream in(SP::_SEEDROOT(signature));
    string line;
    string title, body;
    int startLine = 0, endLine = 0, currentLine = 0;
    bool insideBlock = false;

    while (getline(in, line)) {
        currentLine++;
        if (!insideBlock && line.find('{') != string::npos) {
            title = line;
            startLine = currentLine;
            insideBlock = true;
            body.clear();
        }
        else if (insideBlock) {
            body += line + "\n";
            if (line.find('}') != string::npos) {
                endLine = currentLine;
                blockList.emplace_back(startLine, endLine, title, body);
                insideBlock = false;
            }
        }
    }
}

void Juxtapose::compareBlocks() {
    for (auto& parent : parentBlocks) {
        bool matched = false;
        for (auto& head : headBlocks) {
            if (parent.isTitleEqual(head)) {
                if (!parent.isBodyEqual(head)) {
                    root.MODIFIED(parent);
                }
                matched = true;
                break;
            }
        }
        if (!matched) {
            root.REMOVED(parent);
        }
    }

    for (auto& head : headBlocks) {
        bool matched = false;
        for (auto& parent : parentBlocks) {
            if (head.isTitleEqual(parent)) {
                matched = true;
                break;
            }
        }
        if (!matched) {
            root.ADDED(head);
        }
    }
}





