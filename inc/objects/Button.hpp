/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Button
 *
 * File creation = 24/05/2020
 * Last modification = 24/05/2020
 */

#ifndef __BOMBERMAN_BUTTON_HPP__
#define __BOMBERMAN_BUTTON_HPP__

#include <irrlicht.h>
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include "MacroIndie.hpp"
#include "Sound.hpp"
#include "interface/IVisualObject.hpp"

namespace indie::object {
    class Button : public IVisualObject {
        public:
            static std::string normalSprite_default;
            static std::string pressedSprite_default;
            static std::string hoverSprite_default;
            static unsigned int buttonId;
        struct info_t {
            const std::string s_normalSprite;
            const std::string s_pressedSprite;
            const std::string s_hoverSprite;
            irr::core::rect<irr::s32> s_position;
            indie::macro::ButtonSignal s_signal;

            info_t(irr::core::rect<irr::s32> pos,
                 indie::macro::ButtonSignal sign,
                 std::string normal = normalSprite_default,
                 std::string pressed = pressedSprite_default,
                 std::string hover = hoverSprite_default) :
                s_normalSprite(std::move(normal)),
                s_pressedSprite(std::move(pressed)),
                s_hoverSprite(std::move(hover)),
                s_position(std::move(pos)), s_signal(sign) {}

        };
        public:
            Button(const std::string &text, const std::string &about,
                info_t buttonInfo, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
                std::shared_ptr<irr::video::IVideoDriver> &driver);
            ~Button() = default;
            Button& operator=(const Button &button);
            Button(const Button &button);
            [[nodiscard]] indie::macro::ButtonSignal getSignal() const;
            [[nodiscard]] bool isPressed() const;
            void draw(std::shared_ptr<irr::video::IVideoDriver> &driver) final;

        private:
            irr::gui::IGUISpriteBank *_spriteBank;
            indie::macro::ButtonSignal _signal;
            irr::core::rect<irr::s32> _initPosition;
            std::pair<float, float> _initWindowSize;
            irr::gui::IGUIButton *_button;
            irr::s32 _normalIndex;
            irr::s32 _pressedIndex;
            irr::s32 _hoverIndex;
            indie::object::Sound _sound;
    };
}

#endif //__BOMBERMAN_BUTTON_HPP__
