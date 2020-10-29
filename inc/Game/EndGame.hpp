/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = EndGame
 *
 * File creation = 13/06/2020
 * Last modification = 13/06/2020
 */

#ifndef __BOMBERMAN_ENDGAME_HPP__
#define __BOMBERMAN_ENDGAME_HPP__

#include <banks/PictureBank.hpp>
#include <banks/ButtonBank.hpp>
#include <banks/ObjectBank.hpp>
#include "Engine/Window.hpp"
#include <memory>

namespace indie::game {
    class EndGame {
        public:
            EndGame(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                std::shared_ptr<irr::video::IVideoDriver> videoDriver,
            const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);
            indie::macro::ButtonSignal draw(std::shared_ptr<irr::video::IVideoDriver> &videoDriver);
        private:
            indie::bank::PictureBank _pictureBank;
            indie::bank::ButtonBank _buttonBank;
            indie::bank::ObjectBank _objectBank;

    };
}

#endif //__BOMBERMAN_ENDGAME_HPP__
