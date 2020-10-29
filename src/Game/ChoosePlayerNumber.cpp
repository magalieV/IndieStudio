/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = ChoosePlayerNumber
 *
 * File creation = 13/06/2020
 * Last modification = 13/06/2020
 */

#include "Game/ChoosePlayerNumber.hpp"
#include "Game/MultiplayerGame.hpp"
#include "Game/SplashScreen.hpp"

indie::game::ChoosePlayerNumber::ChoosePlayerNumber()
= default;

indie::game::ChoosePlayerNumber::ChoosePlayerNumber(
    std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    _buttonBank.addButton(indie::object::Button("2", "2 players", indie::object::Button::info_t(irr::core::rect<irr::s32>(740, 240, 1140, 438), indie::macro::_SAVE_2), guiEnvironnement, videoDriver));
    _buttonBank.addButton(indie::object::Button("3", "3 players", indie::object::Button::info_t(irr::core::rect<irr::s32>(740, 478, 1140, 676), indie::macro::_SAVE_3), guiEnvironnement, videoDriver));
    _buttonBank.addButton(indie::object::Button("4", "4 players", indie::object::Button::info_t(irr::core::rect<irr::s32>(740, 716, 1140, 914), indie::macro::_SAVE_4), guiEnvironnement, videoDriver));
    _text = indie::object::Text("How many player?", irr::video::SColor(255, 255, 255, 255), {615, 100, 1000, 200}, guiEnvironnement);
    _objectBank.addObject(&_buttonBank);
    _objectBank.addObject(&_text);
}

bool indie::game::ChoosePlayerNumber::run(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager, std::shared_ptr<irr::video::IVideoDriver> &videoDriver, indie::object::Window *device) {
    indie::macro::ButtonSignal signal = indie::macro::ButtonSignal::_DEFAULT;
    float x = (float(1920 - device->getScreenSize().Width)) / 2.f;
    float y = (float(1080 - device->getScreenSize().Height)) / 2.f;
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    _pictureBank.add(indie::object::Picture("assets/game/player/choosePlayer.png", std::pair<float, float>(x * -1, y * -1), std::pair<float, float>(1920, 1080), videoDriver));
    int number = -1;
    while (device->isRunning()) {
        videoDriver->beginScene(true, true,
                                irr::video::SColor(0, 255, 255, 255));
        _pictureBank.draw(videoDriver);
        sceneManager->drawAll();
        _objectBank.draw(videoDriver);
        signal = _buttonBank.handleEvent();
        videoDriver->endScene();
        if (signal != indie::macro::ButtonSignal::_DEFAULT)
            break;
        if (device->_eventHandler->isKeyReleased(irr::KEY_BACK))
            return true;
    }
    if (signal == indie::macro::ButtonSignal::_SAVE_2) {
        number = 2;
    }
    else if (signal == indie::macro::ButtonSignal::_SAVE_3) {
        number = 3;
    } else if (signal == indie::macro::ButtonSignal::_SAVE_4) {
        number = 4;
    }
    if (number != -1) {
        indie::game::SplashScreen splash(videoDriver, sceneManager, device->getGuiEnvironement());
        splash.run(sceneManager, videoDriver, device);
        indie::game::CreateBoard board(videoDriver, sceneManager);
        MultiplayerGame multi(number, sceneManager, videoDriver, board, device->getGuiEnvironement(),
                              device);
        multi.run(sceneManager, videoDriver, device);
    }
    return false;
}