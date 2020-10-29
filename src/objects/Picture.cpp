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

#include "objects/Picture.hpp"

indie::object::Picture::Picture(const std::string &picturePath,
    const std::pair<float, float> &position,
    const std::pair<float, float> &size,
    std::shared_ptr<irr::video::IVideoDriver> &driver)
{
    irr::io::path spritePath(picturePath.c_str());

    _picture = driver->getTexture(spritePath);
    _position.set(position.first, position.second);
    _rect = irr::core::rect<irr::s32>(0, 0, size.first, size.second);
}

indie::object::Picture::~Picture()
{
}

irr::core::vector2d<irr::s32>   indie::object::Picture::getPosition() const
{
    return _position;
}



irr::core::rect<irr::s32>   indie::object::Picture::getRect() const
{
    return _rect;
}

void indie::object::Picture::setNewRect(irr::core::rect<irr::s32> rect)
{
    _rect = rect;
}

void    indie::object::Picture::draw(std::shared_ptr<irr::video::IVideoDriver> &driver)
{
    driver->draw2DImage(_picture, _position, _rect,
        nullptr, irr::video::SColor (255,255,255,255),
        true);
}

void indie::object::Picture::setPosition(irr::core::vector2d<irr::s32> newPosition)
{
    _position = newPosition;
}