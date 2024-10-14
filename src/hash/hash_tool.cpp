#include <iostream>
#include <string>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <openssl/rand.h>
#include "hash/hash_tool.hpp"

std::string hash_password(const std::string &Password)
{
    unsigned char HASH[SHA256_DIGEST_LENGTH];

    // hashsear la Password
    SHA256(reinterpret_cast<const unsigned char *>(Password.c_str()), Password.size(), HASH);

    // convertirlo a una representacion hexadecimal
    std::ostringstream HexStream;
    for (unsigned char I : HASH)
    {
        HexStream << std::setw(2) << std::setfill('0') << static_cast<int>(I);
    }

    return HexStream.str();
}

bool verify_password(const std::string &Password, const std::string &PasswordHash)
{
    // Hashear y comparar
    std::string hash_entrada = hash_password(Password);
    return hash_entrada == PasswordHash;
}