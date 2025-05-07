#include "Block.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

std::string Block::computeHash(const std::string& str) const {
    unsigned char md[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), md);

    std::ostringstream out;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
        out << std::hex << std::setw(2) << std::setfill('0') << (int)md[i];

    return out.str();
}