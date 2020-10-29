/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = AError
 *
 * File creation = 14/06/2020
 * Last modification = 14/06/2020
 */

#ifndef __BOMBERMAN_AERROR_HPP__
#define __BOMBERMAN_AERROR_HPP__

#include <exception>
#include <iostream>

class AError : public std::exception
{
    public:
        AError(const std::string &message);
        virtual ~AError() noexcept {};
        const char* what() const noexcept override;
    private:
        std::string _message;
};


#endif //__BOMBERMAN_AERROR_HPP__
