/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Pause
 *
 * File creation = 12/06/2020
 * Last modification = 12/06/2020
 */

#ifndef __BOMBERMAN_PAUSE_HPP__
#define __BOMBERMAN_PAUSE_HPP__

#include <banks/PictureBank.hpp>
#include <banks/ButtonBank.hpp>
#include <banks/ObjectBank.hpp>
#include "Engine/Window.hpp"

namespace indie::game {
    class Pause {
        public:
            Pause() = default;
            Pause(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                  std::shared_ptr<irr::video::IVideoDriver> videoDriver,
                  const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement, bool save = true);
            indie::macro::ButtonSignal draw(std::shared_ptr<irr::video::IVideoDriver> &videoDriver);
        private:
            indie::bank::PictureBank _pictureBank;
            indie::bank::ButtonBank _buttonBank;
            indie::bank::ObjectBank _objectBank;
    };
}

#endif //__BOMBERMAN_PAUSE_HPP__
