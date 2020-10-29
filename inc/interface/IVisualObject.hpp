/*
** EPITECH PROJECT, 2019
** temp
** File description:
** temp
*/

#ifndef __BOMBERMAN_IVISUALOBJECT_HPP__
#define __BOMBERMAN_IVISUALOBJECT_HPP__

#include <iostream>
#include <irrlicht.h>
#include <memory>

namespace indie::object {
    class IVisualObject {
        public:
            IVisualObject() = default;
            ~IVisualObject() = default;
            virtual void draw(std::shared_ptr<irr::video::IVideoDriver> &driver) = 0;
    };
}

#endif //__BOMBERMAN_IVISUALOBJECT_HPP__
