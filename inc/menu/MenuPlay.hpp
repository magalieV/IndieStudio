/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = MenuPlay
 *
 * File creation = 04/06/2020
 * Last modification = 04/06/2020
 */

#ifndef __BOMBERMAN_MENUPLAY_HPP__
#define __BOMBERMAN_MENUPLAY_HPP__

#include "Engine/Window.hpp"
#include "banks/ButtonBank.hpp"
#include "banks/ObjectBank.hpp"
#include "banks/PictureBank.hpp"
#include "interface/ISubMenu.hpp"
#include "Game/ChoosePlayer.hpp"

namespace indie::menu {
    class MenuPlay : public ISubMenu {
        public:
            MenuPlay(std::shared_ptr<irr::video::IVideoDriver> &driver,
            const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
                     std::shared_ptr<irr::scene::ISceneManager> &sceneManager);
            bool run(std::shared_ptr<irr::video::IVideoDriver> &driver,
                indie::object::Window *device,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
                     std::shared_ptr<irr::scene::ISceneManager> &sceneManager) final;

        private:
            indie::bank::ObjectBank _objectBank;
            indie::bank::ButtonBank _buttonBank;
            indie::bank::PictureBank _pictureBank;
            indie::game::ChoosePlayer _choosePlayer;
    };
}

#endif //__BOMBERMAN_MENUPLAY_HPP__
