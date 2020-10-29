/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = EventHandler
 *
 * File creation = 06/06/2020
 * Last modification = 06/06/2020
 */

#include "Engine/EventHandler.hpp"
#include <iostream>
#include <IAnimatedMeshSceneNode.h>

indie::engine::EventHandler::EventHandler(irr::IrrlichtDevice *device, std::shared_ptr<irr::video::IVideoDriver> &driver)
{
    _device = device;
    _isClicked = false;
    _mousePosition = irr::core::vector2d<irr::s32>(0, 0);
    _lastKeyPush = irr::KEY_DIVIDE;
    for (irr::u32 index = 0; index < irr::KEY_KEY_CODES_COUNT; index++) {
        _iskeyPressed[index] = false;
    }
    for (irr::u32 index = 0; index < irr::KEY_KEY_CODES_COUNT; index++) {
        _iskeyReleased[index] = false;
    }
}

bool    indie::engine::EventHandler::OnEvent(const irr::SEvent &event)
{
    _lastKeyPush = irr::KEY_DIVIDE;
    _lastKeyReleased = irr::KEY_DIVIDE;
    if (event.EventType == irr::EET_KEY_INPUT_EVENT &&
        event.KeyInput.Key == irr::KEY_ESCAPE &&
        event.KeyInput.PressedDown) {
        _device->closeDevice();
        return true;
    } else if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown) {
        _lastKeyReleased = event.KeyInput.Key;
        _iskeyPressed[event.KeyInput.Key] = event.KeyInput.PressedDown;
        _iskeyReleased[event.KeyInput.Key] = !event.KeyInput.PressedDown;
    } else if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        _lastKeyPush = event.KeyInput.Key;
        _iskeyPressed[event.KeyInput.Key] = event.KeyInput.PressedDown;
        for (irr::u32 index = 0; index < irr::KEY_KEY_CODES_COUNT; index++) {
            _iskeyReleased.at(index) = false;
        }
    } else if (event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN && event.EventType != irr::EET_KEY_INPUT_EVENT) {
        _isClicked = true;
        _mousePosition = irr::core::vector2d<irr::s32>(event.MouseInput.X, event.MouseInput.Y);
    }
    return false;
}


bool    indie::engine::EventHandler::get_mouseClicked()
{
    if (_isClicked) {
        _isClicked = false;
        return true;
    }
    return _isClicked;
}

irr::core::vector2d<irr::s32>   indie::engine::EventHandler::get_mousePosition() const
{
    return _mousePosition;
}

irr::EKEY_CODE indie::engine::EventHandler::getLastKeyPressed()
{
    irr::EKEY_CODE tmp = _lastKeyPush;

    _lastKeyPush = irr::KEY_DIVIDE;
    return tmp;
}

irr::EKEY_CODE indie::engine::EventHandler::getLastKeyReleased()
{
    irr::EKEY_CODE tmp = _lastKeyReleased;

    _lastKeyReleased = irr::KEY_DIVIDE;
    return tmp;
}

bool indie::engine::EventHandler::isKeyPressed(const irr::EKEY_CODE &key)
{
    return _iskeyPressed[key];
}

bool indie::engine::EventHandler::isKeyReleased(const irr::EKEY_CODE &key)
{
    bool keyReleased = _iskeyReleased[key];

    _iskeyReleased[key] = false;
    return keyReleased;
}