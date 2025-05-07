#pragma once
#include "Block.h"
#include <iostream>


class Diff{
    private:
        std::vector<std::pair<std::string, Block>> diff;

    public:

        void ADDED   (const Block& b){ diff.emplace_back("ADDED", b); };
        void REMOVED (const Block& b){ diff.emplace_back("REMOVED", b); };
        void MODIFIED(const Block& b){ diff.emplace_back("MODIFIED", b); };


        bool tryRead(Block& out);

        void readAll(){
            for (auto& [type, block] : diff) {
                std::cout << "[" << type << "] " << block.title << "\n";
            }
        }
};