#pragma once
#include <string>
#include <vector>

class Block {
public:
    int startLine;
    int endLine;
    
    std::string title;  
    std::string title_hash;

    std::string body;     
    std::string body_hash; 

    Block(int start, int end, const std::string& t, const std::string& b)
    : startLine(start), endLine(end), title(t), body(b) {
        title_hash = computeHash(title);
        body_hash = computeHash(body);
    }

    std::string computeHash(const std::string& str) const;
    bool isTitleEqual(const Block& other) const { return title_hash == other.title_hash; }
    bool isBodyEqual(const Block& other) const { return body_hash == other.body_hash; }
};