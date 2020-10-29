/*
** EPITECH PROJECT, 2019
** temp
** File description:
** temp
*/

#ifndef __BOMBERMAN_ICONNEXION_H__
#define __BOMBERMAN_ICONNEXION_H__

#include "Engine/Window.hpp"

namespace indie::connexion
{
    class IConnexion {
        public:
            IConnexion() = default;
            virtual ~IConnexion() = default;
            virtual void init(std::shared_ptr<irr::video::IVideoDriver> &driver,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement) = 0;
            virtual void run(std::shared_ptr<irr::video::IVideoDriver> &driver,
                indie::object::Window *device, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement) = 0;
    };
}

#endif //__BOMBERMAN_ICONNEXION_H__
