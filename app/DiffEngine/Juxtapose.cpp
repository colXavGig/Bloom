#include "Juxtapose.h"
using namespace std;


void Juxtapose::parseMetadata(const string& sign1, const string& sign2, string p){
    //li le folder file et sort les folders et files
    loadBlocks(sign1.c_str(), parentBlocks);
    loadBlocks(sign2.c_str(), headBlocks);

    compareBlocks();
}

void Juxtapose::loadBlocks(const char* signature, vector<Block>& blockList) {
    std::ifstream file(SP::_SEEDROOT(signature));
    if (!file) {
        throw std::runtime_error("Failed to open file: " + SP::_SEEDROOT(signature).string());
    }

    std::string line, title, body;
    int lineStart = 0, lineEnd = 0;
    bool insideBlock = false;

    while (std::getline(file, line)) {
        ++lineEnd;

        if (line.find('{') != std::string::npos) {

            insideBlock = true;
            title = line;
            body.clear();
            lineStart = lineEnd;
        } else if (insideBlock) {
            body += line + "\n";
            if (line.find('}') != std::string::npos) {
 
                Block blk(lineStart, lineEnd, title, body);
                blockList.push_back(blk);
                insideBlock = false;
            }
        }
    }

    file.close();
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





