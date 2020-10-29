/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = ChoosePlayer
 *
 * File creation = 07/06/2020
 * Last modification = 07/06/2020
 */

#ifndef __BOMBERMAN_CHOOSEPLAYER_HPP__
#define __BOMBERMAN_CHOOSEPLAYER_HPP__

#include "objects/Armature.hpp"
#include "Engine/Window.hpp"
#include <vector>
#include <banks/PictureBank.hpp>
#include "banks/ButtonBank.hpp"
#include "objects/Text.hpp"
#include "banks/ObjectBank.hpp"

namespace indie::game {
    class ChoosePlayer {
        public:
            ChoosePlayer();
            ChoosePlayer(std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);
            void run(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                indie::object::Window *device);
        private:
            std::vector<indie::object3D::Armature *> _playerChoice;
            unsigned int _index;
            irr::scene::ICameraSceneNode* _camera;
            indie::bank::ButtonBank _buttonBank;
            indie::bank::PictureBank _pictureBank;
            indie::bank::ObjectBank _objectBank;
            indie::object::Text _text;
    };
}

#endif //__BOMBERMAN_CHOOSEPLAYER_HPP__
