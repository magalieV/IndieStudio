//
// Created by Magalie Vandenbriele on 2019-10-04.
//

#ifndef ENCRYPTION_ENCRYPTION_HPP
#define ENCRYPTION_ENCRYPTION_HPP

#include <iostream>
#include <string>
#include <list>

namespace encrypt
{
    struct t_key_of_encryption
    {
        int s_sum_key;
        int s_sub_key;
        int s_mul_key;
    };
    class Encryption
    {
        public:
            Encryption() = default;
            ~Encryption() = default;
            static std::list<int> listFromChar(const std::list<char> &list);
            static std::list<int> listFromString(const std::list<std::string> &list);
            static std::list<int> listFromFile(const std::string &fileName);
            static void fileFromChar(const std::list<char> &list, const std::string &outputName);
            static void fileFromString(const std::list<std::string> &list, const std::string &outputName);
            static void fileFromFile(const std::string &fileName, const std::string &outputName);
            static t_key_of_encryption generateKey();
    };
}


#endif //ENCRYPTION_ENCRYPTION_HPP
