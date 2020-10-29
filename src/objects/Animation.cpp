/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Animation
 *
 * File creation = 27/05/2020
 * Last modification = 27/05/2020
 */

#include "objects/Animation.hpp"

indie::object::Animation::Animation(const std::string &picturePath,
    const std::pair<float, float> &position,
    const std::pair<float, float> &size,
    std::shared_ptr<irr::video::IVideoDriver> &driver,
    float frameSize, unsigned int frameNumber)
{
    _picture = indie::object::Picture(picturePath, position, size, driver);
    _frameSize = frameSize;
    _totalFrame = frameNumber;
    _actualFrame = 0;
    irr::core::rect<irr::s32 > rect = _picture.getRect();
    rect.LowerRightCorner.X = frameSize;
    _picture.setNewRect(rect);
    _canDraw = false;
}

indie::object::Animation & indie::object::Animation::operator=(const Animation &other)
{
    _picture = other._picture;
    _frameSize = other._frameSize;
    _totalFrame = other._totalFrame;
    _actualFrame = other._actualFrame;
    _picture = other._picture;
    _canDraw = other._canDraw;
    return *this;
}

indie::object::Animation::Animation(const indie::object::Animation &other)
{
    _picture = other._picture;
    _frameSize = other._frameSize;
    _totalFrame = other._totalFrame;
    _actualFrame = other._actualFrame;
    _picture = other._picture;
    _canDraw = other._canDraw;
}

void indie::object::Animation::setPosition(irr::core::vector2d<irr::s32> newPosition)
{
    _picture.setPosition(newPosition);
}

void indie::object::Animation::draw(std::shared_ptr<irr::video::IVideoDriver> &driver)
{
    if (!_canDraw)
        return;
    if (_actualFrame >= _totalFrame) {
        _actualFrame = 0;
        _canDraw = false;
        return;
    }
    irr::core::rect<irr::s32 > rect = _picture.getRect();
    rect.LowerRightCorner.X = float(_actualFrame + 1) * _frameSize;
    rect.UpperLeftCorner.X = float(_actualFrame) * _frameSize;
    _picture.setNewRect(rect);
    _picture.draw(driver);
    _actualFrame++;
}

void indie::object::Animation::reini()
{
    _actualFrame = 0;
}

void indie::object::Animation::setCanDraw()
{
    reini();
    _canDraw = true;
}

bool indie::object::Animation::canDraw()
{
    return _canDraw;
}