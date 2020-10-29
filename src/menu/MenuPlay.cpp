/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = MenuPlay
 *
 * File creation = 04/06/2020
 * Last modification = 04/06/2020
 */

#include <filesystem>
#include "menu/MenuPlay.hpp"
#include "Game/Game.hpp"
#include "Game/SplashScreen.hpp"

indie::menu::MenuPlay::MenuPlay(std::shared_ptr<irr::video::IVideoDriver> &driver,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement, std::shared_ptr<irr::scene::ISceneManager> &sceneManager)
    : _choosePlayer(driver, sceneManager, guiEnvironnement)
{
    _pictureBank.add(MENU_PLAY_XML, driver, guiEnvironnement);
    _buttonBank.addButton(MENU_PLAY_XML, driver, guiEnvironnement);
    _objectBank.addObject(&_pictureBank);
    _objectBank.addObject(&_buttonBank);
}

bool indie::menu::MenuPlay::run(std::shared_ptr<irr::video::IVideoDriver> &driver,
    indie::object::Window *device, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement, std::shared_ptr<irr::scene::ISceneManager> &sceneManager)
{
    indie::macro::ButtonSignal signal = indie::macro::ButtonSignal::_DEFAULT;
    bool backMenu = false;

    sceneManager->clear();
    while (device->isRunning()) {
        driver->beginScene(true, true, irr::video::SColor(0, 255, 255, 255));
        _objectBank.draw(driver);
        device->drawMouseAnimation(driver);
        signal = _buttonBank.handleEvent();
        driver->endScene();
        if (signal == indie::macro::ButtonSignal::_NEW_GAME || (signal == indie::macro::ButtonSignal::_SAVE_1 && std::filesystem::exists(".save/.users/." + device->getUserName() + "_save/.usersave.xml")))
            break;
        if (device->_eventHandler->isKeyReleased(irr::KEY_BACK)) {
            backMenu = true;
            break;
        }
    }
    if (signal == indie::macro::ButtonSignal::_NEW_GAME) {
        sceneManager->clear();
        indie::game::ChoosePlayer choose(driver, sceneManager, guiEnvironnement);
        choose.run(sceneManager, driver, device);
    } else if (signal == indie::macro::ButtonSignal::_SAVE_1) {
        sceneManager->clear();
        indie::game::SplashScreen splash(driver, sceneManager, device->getGuiEnvironement());
        splash.run(sceneManager, driver, device);
        indie::game::Game game;
        game.loadGame(sceneManager, driver, device, guiEnvironnement);
        game.run(sceneManager, driver, device);
    }
    return backMenu;
}