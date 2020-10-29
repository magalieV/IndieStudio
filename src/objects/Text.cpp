/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Text
 *
 * File creation = 04/06/2020
 * Last modification = 04/06/2020
 */

#include "objects/Text.hpp"

#include <utility>
indie::object::Text::Text(const std::string &text,
    const irr::video::SColor &color,
    const irr::core::rect<irr::s32> &pos,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
    const std::string &font)
{
    _color = color;
    _text = text;
    if (font == "DEFAULT")
        _font = guiEnvironnement->getFont("assets/fonts/font/font.xml");
    else
        _font = guiEnvironnement->getFont(font.c_str());
    _pos = pos;
}

void indie::object::Text::draw(std::shared_ptr<irr::video::IVideoDriver> &driver)
{
    if (_font) {
        _font->draw(_text.c_str(), _pos, _color);
    }
}

void indie::object::Text::setText(const std::string &text)
{
    _text = text;
}

indie::object::Text & indie::object::Text::operator=(const Text &other)
{
    _text = other._text;
    _color = other._color;
    _font = other._font;
    _pos = other._pos;
    return *this;
}