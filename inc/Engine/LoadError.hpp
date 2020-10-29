/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = LoadError
 *
 * File creation = 14/06/2020
 * Last modification = 14/06/2020
 */

#ifndef __BOMBERMAN_LOADERROR_HPP__
#define __BOMBERMAN_LOADERROR_HPP__

#include "AError.hpp"

#define CANT_OPEN(fileName) std::string("Can't open the map '") + fileName + std::string("'")

class LoadError : public AError {
    public:
        LoadError(const std::string &message);
        virtual ~LoadError() noexcept {};

};

#endif //__BOMBERMAN_LOADERROR_HPP__
