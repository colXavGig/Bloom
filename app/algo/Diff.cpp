#include "Diff.h"
void Diff::ensureCapacity() {
    if (size >= capacity) {
        capacity *= 2;
        diff = static_cast<Block*>(realloc(diff, capacity * sizeof(Block)));
    }
}
void Diff::ADDED(const Block& b) {
    ensureCapacity();
    diff[size++] = b; // shallow copy
    std::cout << "[+ADDED] " << b.title << "\n";
}

void Diff::REMOVED(const Block& b) {
    ensureCapacity();
    diff[size++] = b;
    std::cout << "[-REMOVED] " << b.title << "\n";
}

void Diff::MODIFIED(const Block& b) {
    ensureCapacity();
    diff[size++] = b;
    std::cout << "[~MODIFIED] " << b.title << "\n";
}



bool Diff:: tryRead(Block& out){
    if(size < 0)
        return false;
    out = diff[size--];
    return true;
}

void Diff::readAll() {
    for (size_t i = 0; i < size; ++i) {
        std::cout << "Block [" << diff[i].startLine << "-" << diff[i].endLine << "]: " << diff[i].title << "\n";
    }
}