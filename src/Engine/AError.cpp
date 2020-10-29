/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = AError
 *
 * File creation = 14/06/2020
 * Last modification = 14/06/2020
 */

#include "Engine/AError.hpp"

AError::AError(const std::string &message)
{
    _message = message;
}

const char * AError::what() const noexcept
{
    return _message.c_str();
}