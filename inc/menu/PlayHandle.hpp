/*
** EPITECH PROJECT, 2019
** temp
** File description:
** temp
*/

#ifndef __BOMBERMAN_PLAYHANDLE_HPP__
#define __BOMBERMAN_PLAYHANDLE_HPP__

#include "menu/MenuPlay.hpp"
#include "MacroIndie.hpp"
#include "interface/ISubMenu.hpp"
#include <map>
#include <functional>
#include "Engine/Window.hpp"

namespace indie::menu {
    const std::map<indie::macro::ButtonSignal, std::function<std::unique_ptr<ISubMenu>(std::shared_ptr<irr::video::IVideoDriver> &driver,
        const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement, std::shared_ptr<irr::scene::ISceneManager> &sceneManager)> > subMenuRedirection = {
        {indie::macro::ButtonSignal::_PLAY, [](std::shared_ptr<irr::video::IVideoDriver> &driver,
            const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement, std::shared_ptr<irr::scene::ISceneManager> &sceneManager) {
            return std::unique_ptr<ISubMenu>(new MenuPlay(driver, guiEnvironnement, sceneManager)); }},
    };
}

#endif //__BOMBERMAN_PLAYHANDLE_HPP__
