/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Menu
 *
 * File creation = 27/05/2020
 * Last modification = 27/05/2020
 */

#ifndef __BOMBERMAN_MENU_HPP__
#define __BOMBERMAN_MENU_HPP__

#include "Engine/Window.hpp"
#include "banks/ButtonBank.hpp"
#include "banks/ObjectBank.hpp"
#include "banks/PictureBank.hpp"
#include "MenuPlay.hpp"

namespace indie::menu {
    class Menu {
        public:
            Menu(std::shared_ptr<irr::video::IVideoDriver> &driver,
             const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
             std::shared_ptr<irr::scene::ISceneManager> &sceneManager);
            void run(std::shared_ptr<irr::video::IVideoDriver> &driver,
                indie::object::Window *device,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
                     std::shared_ptr<irr::scene::ISceneManager> &sceneManager);

        private:
            indie::bank::ObjectBank _objectBank;
            indie::bank::ButtonBank _buttonBank;
            indie::bank::PictureBank _pictureBank;
            indie::menu::MenuPlay _menuPlay;
    };
}

#endif //__BOMBERMAN_MENU_HPP__
