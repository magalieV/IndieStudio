/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Form
 *
 * File creation = 04/06/2020
 * Last modification = 04/06/2020
 */

#ifndef __BOMBERMAN_FORM_HPP__
#define __BOMBERMAN_FORM_HPP__

#include "interface/IVisualObject.hpp"
#include "objects/Text.hpp"

namespace indie::object {
    class Form : public IVisualObject {
        public:
            Form() = default;
            Form(const irr::core::rect<irr::s32> &pos, unsigned int size,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
                const std::string &name, const irr::video::SColor &boxColor,
                const irr::video::SColor &textColor, bool password = false,
                const std::string &font = "assets/fonts/font/font.xml");
            void draw(std::shared_ptr<irr::video::IVideoDriver> &driver) final;
            [[nodiscard]] std::string getInput() const;
            Form& operator=(const Form &other);
            Form(const Form &other);

        private:
            irr::gui::IGUIEditBox* _box;
            indie::object::Text _text;
            irr::gui::IGUIFont *_font;
    };
}

#endif //__BOMBERMAN_FORM_HPP__
