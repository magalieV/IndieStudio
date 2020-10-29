/*
** EPITECH PROJECT, 2019
** temp
** File description:
** temp
*/

#include "../inc/Decryption.hpp"
#include <fstream>

std::list<char> encrypt::Decryption::listFromInt(const std::list<int> &list)
{
    std::list<char> encryptValue;
    unsigned int counter = 0;
    encrypt::t_key_of_encryption key;

    for (const auto &number : list) {
        switch (counter) {
            case 0:
                key.s_sum_key = number;
                break;
            case 1:
                key.s_sub_key = number;
                break;
            case 2:
                key.s_mul_key = number;
                break;
            default:
                int nb = number;
                nb /= key.s_mul_key;
                nb += key.s_sub_key;
                nb -= key.s_sum_key;
                encryptValue.emplace_back(char(nb));
                break;
        }
        counter++;
    }
    return encryptValue;
}

std::list<char> encrypt::Decryption::listFromFile(const std::string &fileName)
{
    std::ifstream flux(fileName, std::ios::binary);
    std::list<int> valueToDecrypt;
    int tmp = 0;

    if (!flux)
        return std::list<char>();
    while (!flux.eof()) {
        flux.read((char*)&tmp, sizeof(tmp));
        valueToDecrypt.push_back(tmp);
    }
    flux.close();
    return encrypt::Decryption::listFromInt(valueToDecrypt);
}

std::list<std::string> encrypt::Decryption::stringFromInt(const std::list<int> &list)
{
    std::list<char> value = encrypt::Decryption::listFromInt(list);
    std::list<std::string> newList;
    std::string tmp;

    for (const auto &letter : value) {
        if (letter == '\n') {
            newList.push_back(tmp);
            tmp.clear();
        } else {
            tmp.push_back(letter);
        }
    }
    if (!tmp.empty()) {
        newList.push_back(tmp);
    }
    return newList;
}

std::list<std::string> encrypt::Decryption::stringFromFile(const std::string &fileName)
{
    std::list<char> value = encrypt::Decryption::listFromFile(fileName);
    std::list<std::string> newList;
    std::string tmp;

    for (const auto &letter : value) {
        if (letter == '\n') {
            newList.push_back(tmp);
            tmp.clear();
        } else {
            tmp.push_back(letter);
        }
    }
    if (!tmp.empty()) {
        newList.push_back(tmp);
    }
    return newList;
}

void encrypt::Decryption::fileFromInt(const std::list<int> &list, const std::string &fileName)
{
    std::list<char> values;

    values = encrypt::Decryption::listFromInt(list);
    std::ofstream flux(fileName);
    if (!flux)
        return;
    for (const auto &letter : values) {
        flux << letter;
    }
    flux.close();
}

void encrypt::Decryption::fileFromFile(const std::string &fileName, const std::string &ouputFile)
{
    std::list<char> values;

    values = encrypt::Decryption::listFromFile(ouputFile);
    std::ofstream flux(fileName);
    if (!flux)
        return;
    for (const auto &letter : values) {
        flux << letter;
    }
    flux.close();
}