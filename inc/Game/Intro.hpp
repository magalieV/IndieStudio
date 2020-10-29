/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Intro
 *
 * File creation = 10/06/2020
 * Last modification = 10/06/2020
 */

#ifndef __BOMBERMAN_INTRO_HPP__
#define __BOMBERMAN_INTRO_HPP__

#include "objects/StaticObject.hpp"
#include "Engine/Window.hpp"
#include <vector>
#include <banks/PictureBank.hpp>
#include "banks/ButtonBank.hpp"
#include "objects/Text.hpp"
#include "banks/ObjectBank.hpp"
#include "objects/Player.hpp"

namespace indie::game {
    class Intro {
        public:
            Intro(std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
            const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
            const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);
            void run(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                     std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                     indie::object::Window *device);
        private:
            indie::object3D::StaticObject _indieName;
            irr::scene::ICameraSceneNode* _camera;
            std::vector<indie::object3D::Player> _allPlayer;
            std::vector<indie::object3D::Armature *> _playerChoice;
            unsigned int _index;
    };
}

#endif //__BOMBERMAN_INTRO_HPP__
