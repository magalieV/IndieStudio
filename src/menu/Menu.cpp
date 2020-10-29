/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Menu
 *
 * File creation = 27/05/2020
 * Last modification = 27/05/2020
 */

#include "menu/Menu.hpp"
#include "MacroIndie.hpp"
#include "banks/PictureBank.hpp"
#include "menu/PlayHandle.hpp"
#include "Game/ChoosePlayerNumber.hpp"

indie::menu::Menu::Menu(std::shared_ptr<irr::video::IVideoDriver> &driver,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
    std::shared_ptr<irr::scene::ISceneManager> &sceneManager) : _menuPlay(driver, guiEnvironnement, sceneManager)
{
    _pictureBank.add(MENU_XML, driver, guiEnvironnement);
    _buttonBank.addButton(MENU_XML, driver, guiEnvironnement);
    _objectBank.addObject(&_pictureBank);
    _objectBank.addObject(&_buttonBank);
}

void indie::menu::Menu::run(std::shared_ptr<irr::video::IVideoDriver> &driver,
    indie::object::Window *device, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
    std::shared_ptr<irr::scene::ISceneManager> &sceneManager)
{
    indie::macro::ButtonSignal signal = indie::macro::ButtonSignal::_DEFAULT;
    std::shared_ptr<indie::menu::ISubMenu> subMenu;
    bool relaunch = false;

    while (device->isRunning()) {
        driver->beginScene(true, true, irr::video::SColor(0, 255, 255, 255));
        _objectBank.draw(driver);
        device->drawMouseAnimation(driver);
        signal = _buttonBank.handleEvent();
        if (signal == indie::macro::ButtonSignal::_QUIT)
            break;
        driver->endScene();
        if (signal == indie::macro::ButtonSignal::_PLAY) {
            relaunch = _menuPlay.run(driver, device, guiEnvironnement, sceneManager);
        } else if (signal == indie::macro::ButtonSignal::_MULTI) {
            sceneManager->clear();
            indie::game::ChoosePlayerNumber mutli(driver, sceneManager, guiEnvironnement);
            relaunch = mutli.run(sceneManager, driver, device);
        }
    }
}