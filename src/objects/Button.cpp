/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Button
 *
 * File creation = 24/05/2020
 * Last modification = 24/05/2020
 */

#include "objects/Button.hpp"
#include <string>

std::string indie::object::Button::normalSprite_default = "assets/connection/button/normal.png";
std::string indie::object::Button::pressedSprite_default = "assets/connection/button/pressed.png";
std::string indie::object::Button::hoverSprite_default = "assets/connection/button/hover.png";
unsigned int indie::object::Button::buttonId = 0;

indie::object::Button::Button(const std::string &text, const std::string &about,
    info_t buttonInfo,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
    std::shared_ptr<irr::video::IVideoDriver> &driver)
    : _spriteBank(guiEnvironnement->addEmptySpriteBank((std::string("icons") + std::to_string(buttonId)).c_str()))
{
    std::wstring buttonText = std::wstring(text.begin(), text.end());
    std::wstring buttonAbout = std::wstring(about.begin(), about.end());
    irr::gui::IGUIFont *font = guiEnvironnement->getFont("assets/fonts/font/font.xml");

    buttonId += 1;
    irr::gui::IGUISkin *skin = guiEnvironnement->getSkin();
    if (font != nullptr) {
        skin->setFont(font);
        skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 0, 0, 0));
    }
    _signal = buttonInfo.s_signal;
    _button = guiEnvironnement->addButton(buttonInfo.s_position, nullptr, -1, buttonText.c_str(), buttonAbout.c_str());
    _button->setOverrideFont(font);
    if (buttonInfo.s_normalSprite == "DEFAULT")
        _normalIndex = _spriteBank->addTextureAsSprite(driver->getTexture(indie::object::Button::normalSprite_default.c_str()));
    else
        _normalIndex = _spriteBank->addTextureAsSprite(driver->getTexture(buttonInfo.s_normalSprite.c_str()));
    if (buttonInfo.s_pressedSprite == "DEFAULT")
        _pressedIndex = _spriteBank->addTextureAsSprite(driver->getTexture(indie::object::Button::pressedSprite_default.c_str()));
    else
        _pressedIndex = _spriteBank->addTextureAsSprite(driver->getTexture(buttonInfo.s_pressedSprite.c_str()));
    if (buttonInfo.s_hoverSprite == "DEFAULT")
        _hoverIndex = _spriteBank->addTextureAsSprite(driver->getTexture(indie::object::Button::hoverSprite_default.c_str()));
    else
        _hoverIndex = _spriteBank->addTextureAsSprite(driver->getTexture(buttonInfo.s_hoverSprite.c_str()));
    _button->setSpriteBank(_spriteBank);
    _button->setSprite(irr::gui::EGBS_BUTTON_UP, _normalIndex);
    _button->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OVER, _hoverIndex);
    _button->setSprite(irr::gui::EGBS_BUTTON_DOWN, _pressedIndex);
    _initWindowSize.first = 1920;
    _initWindowSize.second = 1080;
    _initPosition = buttonInfo.s_position;
    _button->setUseAlphaChannel(true);
    _button->setDrawBorder(0);
    _sound = indie::object::Sound("assets/button/Dart.ogg");
}

indie::object::Button& indie::object::Button::operator=(const Button &button)
{
    _spriteBank = button._spriteBank;
    _signal = button._signal;
    _initPosition = button._initPosition;
    _initWindowSize = button._initWindowSize;
    _button = button._button;
    _normalIndex = button._normalIndex;
    _pressedIndex = button._pressedIndex;
    _hoverIndex = button._hoverIndex;
    _sound = button._sound;
    return *this;
}

indie::object::Button::Button(const indie::object::Button &button)
{
    _spriteBank = button._spriteBank;
    _signal = button._signal;
    _initPosition = button._initPosition;
    _initWindowSize = button._initWindowSize;
    _button = button._button;
    _normalIndex = button._normalIndex;
    _pressedIndex = button._pressedIndex;
    _hoverIndex = button._hoverIndex;
    _sound = button._sound;
}

bool indie::object::Button::isPressed() const
{
    return _button->isPressed();
}

indie::macro::ButtonSignal indie::object::Button::getSignal() const
{
    return _signal;
}

void indie::object::Button::draw(std::shared_ptr<irr::video::IVideoDriver> &driver)
{
    if (driver->getScreenSize().Width != _initWindowSize.first || driver->getScreenSize().Height != _initWindowSize.second) {
        float percentageX = driver->getScreenSize().Width * 100 / _initWindowSize.first;
        float percentageY = driver->getScreenSize().Height * 100 / _initWindowSize.second;
        irr::core::vector2d<int> upperCorner = _initPosition.UpperLeftCorner;
        irr::core::vector2d<int> lowerCorner = _initPosition.LowerRightCorner;
        irr::core::rect<irr::s32> newPos(upperCorner.X * percentageX / 100,
                                         upperCorner.Y * percentageY / 100,
                                         lowerCorner.X * percentageX / 100,
                                         lowerCorner.Y * percentageY / 100);

        _button->setRelativePosition(newPos);
        _initPosition = newPos;
        _initWindowSize.first = driver->getScreenSize().Width;
        _initWindowSize.second = driver->getScreenSize().Height;
    }
    if (_button->isPressed()) {
        _sound.play();
        _button->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OVER, _pressedIndex);
    } else {
        _button->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OVER, _hoverIndex);
    }
    _button->draw();
}