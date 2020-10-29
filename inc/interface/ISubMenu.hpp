/*
** EPITECH PROJECT, 2019
** temp
** File description:
** temp
*/

#ifndef __BOMBERMAN_SUBMENU_HPP__
#define __BOMBERMAN_SUBMENU_HPP__

#include "Engine/Window.hpp"

namespace indie::menu
{
    class ISubMenu {
        public:
            ISubMenu() = default;
            ~ISubMenu() = default;
            virtual bool run(std::shared_ptr<irr::video::IVideoDriver> &driver,
                indie::object::Window *device,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
                std::shared_ptr<irr::scene::ISceneManager> &sceneManager) = 0;
    };
}

#endif //__BOMBERMAN_SUBMENU_HPP__
