/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Text
 *
 * File creation = 04/06/2020
 * Last modification = 04/06/2020
 */

#ifndef __BOMBERMAN_TEXT_HPP__
#define __BOMBERMAN_TEXT_HPP__

#include "interface/IVisualObject.hpp"
#include <iostream>
#include <memory>

namespace indie::object {
    class Text : public IVisualObject {
        public:
            Text(const std::string &text,
                const irr::video::SColor &color,
                const irr::core::rect<irr::s32> &pos,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
                const std::string &font = "assets/fonts/font/font.xml");
            Text& operator=(const Text &other);
            Text() = default;
            void draw(std::shared_ptr<irr::video::IVideoDriver> &driver) final;
            void setText(const std::string &text);

        private:
            std::string _text;
            irr::video::SColor _color;
            irr::core::rect<irr::s32> _pos;
            irr::gui::IGUIFont *_font;
    };
}

#endif //__BOMBERMAN_TEXT_HPP__
