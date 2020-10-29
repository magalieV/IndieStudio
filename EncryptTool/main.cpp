/*
** EPITECH PROJECT, 2019
** temp
** File description:
** temp
*/

#include "inc/Encryption.hpp"
#include "inc/Decryption.hpp"
#include <iostream>

int main(int ac, char *argv[])
{
    if (ac < 4)
        return 84;
    if (std::string(argv[3]) == "-e") {
        encrypt::Encryption::fileFromFile(argv[1], argv[2]);
    } else {
        encrypt::Decryption::fileFromFile(argv[1], argv[2]);
    }
    return 0;
}