/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = ChoosePlayerNumber
 *
 * File creation = 13/06/2020
 * Last modification = 13/06/2020
 */

#ifndef __BOMBERMAN_CHOOSEPLAYERNUMBER_HPP__
#define __BOMBERMAN_CHOOSEPLAYERNUMBER_HPP__

#include "objects/Armature.hpp"
#include "Engine/Window.hpp"
#include <vector>
#include <banks/PictureBank.hpp>
#include "banks/ButtonBank.hpp"
#include "objects/Text.hpp"
#include "banks/ObjectBank.hpp"

namespace indie::game {
    class ChoosePlayerNumber {
        public:
            ChoosePlayerNumber();
            ChoosePlayerNumber(std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
            const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
            const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);
            bool run(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                indie::object::Window *device);
        private:
            indie::bank::ButtonBank _buttonBank;
            indie::bank::PictureBank _pictureBank;
            indie::bank::ObjectBank _objectBank;
            indie::object::Text _text;
    };
}

#endif //__BOMBERMAN_CHOOSEPLAYERNUMBER_HPP__
