#include "Diff.h"


bool Diff:: tryRead(Block& out){
    if (diff.empty()) return false;
    out = diff.back().second;
    diff.pop_back();
    return true;
}

void Diff::readAll() {
    for (const auto& [type, block] : diff) {
        std::cout << "[" << type << "] " << block.title << "\n";
    }

    for (const auto& [head, target] : conflicts) {
        std::cout << "[CONFLICT] " << head.title << "\n";
        std::cout << "<<<<<<< HEAD\n" << head.body << "\n";
        std::cout << "=======\n" << target.body << "\n";
        std::cout << ">>>>>>>\n";
    }
}

void Diff::merge(const Diff& other) {
    for (const auto& [type, block] : other.diff) {
        diff.emplace_back(type, block);
    }
    for (const auto& [head, target] : other.conflicts) {
        conflicts.emplace_back(head, target);
    }
}