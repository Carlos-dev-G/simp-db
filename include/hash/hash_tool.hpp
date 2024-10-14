#ifndef HASH_TOOL_HPP
#define HASH_TOOL_HPP
#include <string>

std::string hash_password(const std::string &Password);
bool verify_password(const std::string &Password, const std::string &PasswordHash);

#endif // HASH_TOOL_HPP
