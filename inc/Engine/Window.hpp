/*
 * Project Name = bomberman
 *
 * Author = magalie.vandenbriele | irama.chaouch | theodore.faraut-schwieg
 * | paul.riba | cesar.venzac
 * Object = Window
 *
 * File creation = 22/05/2020
 * Last modification = 22/05/2020
 */

#ifndef __BOMBERMAN_WINDOW_HPP__
#define __BOMBERMAN_WINDOW_HPP__

#include <irrlicht.h>
#include <iostream>
#include <memory>
#include "objects/Animation.hpp"
#include "Engine/EventHandler.hpp"
#include "banks/ObjectBank.hpp"

namespace indie::object {
    class Window {
        public:
            Window(const std::string &name,
                const std::pair<float, float> &dimension,
                unsigned int bits);
            ~Window();
            [[nodiscard]] bool windowExist() const;
            [[nodiscard]] bool isRunning() const;
            [[nodiscard]] bool isActive() const;
            [[nodiscard]] std::shared_ptr<irr::video::IVideoDriver> getVideoDriver() const;
            [[nodiscard]] std::shared_ptr<irr::scene::ISceneManager> getSceneManager() const;
            [[nodiscard]] std::shared_ptr<irr::gui::IGUIEnvironment> getGuiEnvironement() const;
            void closeDevice();
            void drop() const;
            irr::EKEY_CODE getLastKeyPressed();
            irr::EKEY_CODE getLastKeyReleased();
            void drawMouseAnimation(std::shared_ptr<irr::video::IVideoDriver> &driver);
            indie::engine::EventHandler *_eventHandler;
            [[nodiscard]] irr::u32 getTime() const;
            irr::core::dimension2d<irr::u32> getScreenSize();
            void setUserName(const std::string &name);
            std::string getUserName() const;

        private:
            std::shared_ptr<irr::IrrlichtDevice> _device;
            std::shared_ptr<irr::video::IVideoDriver> _videoDriver;
            std::shared_ptr<irr::scene::ISceneManager> _sceneManager;
            std::shared_ptr<irr::gui::IGUIEnvironment> _guiEnvironnement;
            indie::object::Animation *_mouseAnimation;
            std::string _userName;
    };
}

#endif //__BOMBERMAN_WINDOW_HPP__
