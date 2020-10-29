//
// Created by Magalie Vandenbriele on 2019-10-04.
//

#include "../inc/Encryption.hpp"
#include <fstream>

encrypt::t_key_of_encryption encrypt::Encryption::generateKey()
{
    encrypt::t_key_of_encryption key;

    key.s_sum_key = rand() % 100;
    key.s_sub_key = rand() % 100;
    key.s_mul_key = rand() % 10 + 1;
    return key;
}

std::list<int> encrypt::Encryption::listFromChar(const std::list<char> &list)
{
    std::list<int> encryptFile;
    encrypt::t_key_of_encryption key = encrypt::Encryption::generateKey();

    encryptFile.emplace_back(key.s_sum_key);
    encryptFile.emplace_back(key.s_sub_key);
    encryptFile.emplace_back(key.s_mul_key);
    for (const auto &letter : list) {
        int number = letter;
        number += key.s_sum_key;
        number -= key.s_sub_key;
        number *= key.s_mul_key;
        encryptFile.emplace_back(number);
    }
    return encryptFile;
}

std::list<int> encrypt::Encryption::listFromString(const std::list<std::string> &list)
{
    std::list<char> newList;

    for (const auto &line : list) {
        for (const auto &letter : line) {
            newList.push_back(letter);
        }
        newList.push_back('\n');
    }
    return encrypt::Encryption::listFromChar(newList);
}

std::list<int> encrypt::Encryption::listFromFile(const std::string &fileName)
{
    std::ifstream flux(fileName);
    std::list<std::string> fileLines;
    std::string tmp;

    if (!flux) {
        return std::list<int>();
    }
    while(getline(flux, tmp)) {
        fileLines.push_back(tmp);
    }
    flux.close();
    return encrypt::Encryption::listFromString(fileLines);
}

void encrypt::Encryption::fileFromChar(const std::list<char> &list, const std::string &outputName)
{
    std::list<int> encryptList;

    encryptList = encrypt::Encryption::listFromChar(list);
    std::ofstream flux(outputName, std::ios::binary);
    if (!flux)
        return;
    for (const auto &number : encryptList) {
        int nb = number;
        flux.write((char*)&nb, sizeof(nb));
    }
    flux.close();
}

void encrypt::Encryption::fileFromString(const std::list<std::string> &list, const std::string &outputName)
{
    std::list<int> encryptList;

    encryptList = encrypt::Encryption::listFromString(list);
    std::ofstream flux(outputName, std::ios::binary);
    if (!flux)
        return;
    for (const auto &number : encryptList) {
        int nb = number;
        flux.write((char*)&nb, sizeof(nb));
    }
    flux.close();
}

void encrypt::Encryption::fileFromFile(const std::string &fileName, const std::string &outputName)
{
    std::list<int> encryptList;

    encryptList = encrypt::Encryption::listFromFile(fileName);
    std::ofstream flux(outputName, std::ios::binary);
    if (!flux)
        return;
    for (const auto &number : encryptList) {
        int nb = number;
        flux.write((char *) &nb, sizeof(nb));
    }
    flux.close();
}