/*
 * Project Name = bomberman
 *
 * Author = magalie.vandenbriele | irama.chaouch | theodore.faraut-schwieg
 * | paul.riba | cesar.venzac
 * Object = Picture
 *
 * File creation = 22/05/2020
 * Last modification = 22/05/2020
 */

#ifndef __BOMBERMAN_PICTURE_HPP__
#define __BOMBERMAN_PICTURE_HPP__

#include <irrlicht.h>
#include <iostream>
#include <memory>
#include "interface/IVisualObject.hpp"

namespace indie::object {
    class Picture : public IVisualObject {
        public:
            Picture() = default;
            Picture(const std::string &picturePath,
                    const std::pair<float, float> &position,
                    const std::pair<float, float> &size,
                    std::shared_ptr<irr::video::IVideoDriver> &driver);
            ~Picture();
            void setNewRect(irr::core::rect<irr::s32> rect);
            [[nodiscard]] irr::core::position2d<irr::s32> getPosition() const;
            [[nodiscard]] irr::core::rect<irr::s32> getRect() const;
            void setPosition(irr::core::position2d<irr::s32> newPosition);
            void draw(std::shared_ptr<irr::video::IVideoDriver> &driver) final;

        private:
            irr::video::ITexture *_picture;
            irr::core::position2d<irr::s32> _position;
            irr::core::rect<irr::s32> _rect;
    };
}

#endif //__BOMBERMAN_PICTURE_HPP__
