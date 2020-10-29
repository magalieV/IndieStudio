/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Form
 *
 * File creation = 04/06/2020
 * Last modification = 04/06/2020
 */

#include "objects/Form.hpp"

indie::object::Form::Form(const irr::core::rect<irr::s32> &pos, unsigned int size,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
    const std::string &name,
    const irr::video::SColor &boxColor,
    const irr::video::SColor &textColor, bool password,
    const std::string &font)
{
    irr::core::rect<irr::s32> textPos = pos;

    _box = guiEnvironnement->addEditBox(L"", pos);
    _box->setMax(size);
    if (font == "DEFAULT")
        _font = guiEnvironnement->getFont("assets/fonts/font/font.xml");
    else
        _font = guiEnvironnement->getFont(font.c_str());
    _box->setOverrideFont(_font);
    _box->setOverrideColor(boxColor);
    if (password)
        _box->setPasswordBox(true, '*');
    textPos.UpperLeftCorner.X -= 90;
    textPos.LowerRightCorner.X = textPos.UpperLeftCorner.X + 50;
    textPos.UpperLeftCorner.Y -= 70;
    textPos.LowerRightCorner.Y = textPos.UpperLeftCorner.Y + 25;
    _text = indie::object::Text(name, textColor, textPos, guiEnvironnement);
}

std::string indie::object::Form::getInput() const
{
    std::wstring tmp;

    tmp = static_cast<irr::core::stringw>(_box->getText()).c_str();
    return std::string(tmp.begin(), tmp.end());
}

void indie::object::Form::draw(std::shared_ptr<irr::video::IVideoDriver> &driver)
{
    _box->draw();
    _text.draw(driver);
}

indie::object::Form::Form(const Form &other)
{
    _box = other._box;
    _text = other._text;
    _font = other._font;
}

indie::object::Form & indie::object::Form::operator=(const Form &other)
{
    _box = other._box;
    _text = other._text;
    _font = other._font;
    return *this;
}