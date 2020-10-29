/*
** EPITECH PROJECT, 2019
** temp
** File description:
** temp
*/

#ifndef ENCRYPT_DECRYPTION_HPP
#define ENCRYPT_DECRYPTION_HPP

#include "Encryption.hpp"

namespace encrypt
{
    class Decryption
    {
        public:
            Decryption() = default;
            ~Decryption() = default;
            static std::list<char> listFromInt(const std::list<int> &list);
            static std::list<char> listFromFile(const std::string &fileName);
            static std::list<std::string> stringFromInt(const std::list<int> &list);
            static std::list<std::string> stringFromFile(const std::string &fileName);
            static void fileFromInt(const std::list<int> &list, const std::string &fileName);
            static void fileFromFile(const std::string &fileName, const std::string &ouputFile);
    };
}

#endif //ENCRYPT_DECRYPTION_HPP
