#pragma once
#include "Block.h"
#include <iostream>


class Diff{
    private:
        std::vector<std::pair<std::string, Block>> diff;
        std::vector<std::pair<Block, Block>> conflicts;
    public:
        void ADDED   (const Block& b){ diff.emplace_back("ADDED", b); }
        void REMOVED (const Block& b){ diff.emplace_back("REMOVED", b); }
        void MODIFIED(const Block& b){ diff.emplace_back("MODIFIED", b); }

        void CONFLICTED(const Block& headBlock, const Block& targetBlock) {
            conflicts.emplace_back(headBlock, targetBlock);
        }
        bool hasConflicts() const { return !conflicts.empty();}

        void merge(const Diff& other);



        bool tryRead(Block& out);

        void readAll();
};