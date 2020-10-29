/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = SplashScreen
 *
 * File creation = 14/06/2020
 * Last modification = 14/06/2020
 */

#ifndef __BOMBERMAN_SPLASHSCREEN_HPP__
#define __BOMBERMAN_SPLASHSCREEN_HPP__

#include "Engine/Window.hpp"
#include "objects/Text.hpp"

namespace indie::game {
    class SplashScreen {
        public:
            SplashScreen(std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
            const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
            const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);
            void run(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                     std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                     indie::object::Window *device);
        private:
            indie::object::Text _myText;
            indie::object::Text _info;
    };
}

#endif //__BOMBERMAN_SPLASHSCREEN_HPP__
