/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = ButtonBank
 *
 * File creation = 24/05/2020
 * Last modification = 24/05/2020
 */

#ifndef __BOMBERMAN_BUTTONBANK_HPP__
#define __BOMBERMAN_BUTTONBANK_HPP__

#include "objects/Button.hpp"
#include <list>
#include "interface/IVisualObject.hpp"

namespace indie::bank {
    class ButtonBank : public indie::object::IVisualObject {
        public:
            ButtonBank() = default;
            ~ButtonBank() = default;
            [[nodiscard]] indie::macro::ButtonSignal handleEvent() const;
            void addButton(indie::object::Button button);
            void draw(std::shared_ptr<irr::video::IVideoDriver> &driver) final;
            void addButton(const std::string &configFile, std::shared_ptr<irr::video::IVideoDriver> &driver,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);
            void addButton(std::shared_ptr<irr::video::IVideoDriver> &driver,
            const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement, const std::map<std::string, std::string> info);

        private:
            std::list<indie::object::Button> _buttonList;
    };
}

#endif //__BOMBERMAN_BUTTONBANK_HPP__
