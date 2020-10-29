/*
 * Project Name = bomberman
 *
 * Author = magalie.vandenbriele | irama.chaouch | theodore.faraut-schwieg
 * | paul.riba | cesar.venzac
 * Object = ConnexionBoard
 *
 * File creation = 22/05/2020
 * Last modification = 22/05/2020
 */

#ifndef __BOMBERMAN_CONNEXIONBOARD_HPP__
#define __BOMBERMAN_CONNEXIONBOARD_HPP__

#include "Engine/Window.hpp"
#include "objects/Picture.hpp"
#include "banks/ButtonBank.hpp"
#include "banks/PictureBank.hpp"
#include "banks/ObjectBank.hpp"

namespace indie::connexion
{
    class ConnexionBoard
    {
        public:
            ConnexionBoard(std::shared_ptr<irr::video::IVideoDriver> &driver,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);
            ~ConnexionBoard();
            void run(std::shared_ptr<irr::video::IVideoDriver> &driver,
                indie::object::Window *device,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);

        private:
            indie::bank::PictureBank _pictureBank;
            indie::bank::ButtonBank _buttonBank;
            indie::bank::ObjectBank _objectBank;
    };
}

#endif //__BOMBERMAN_CONNEXIONBOARD_HPP__
