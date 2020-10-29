/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = FormBank
 *
 * File creation = 04/06/2020
 * Last modification = 04/06/2020
 */

#ifndef __BOMBERMAN_FORMBANK_HPP__
#define __BOMBERMAN_FORMBANK_HPP__

#include "interface/IVisualObject.hpp"
#include "objects/Form.hpp"
#include <map>

namespace indie::bank {
    class FormBank : public indie::object::IVisualObject {
        public:
            FormBank() = default;
            void add(indie::object::Form form, const std::string &name);
            [[nodiscard]] std::map<std::string, std::string> getInputs() const;
            void draw(std::shared_ptr<irr::video::IVideoDriver> &driver) final;
            void add(const std::string &configFile, std::shared_ptr<irr::video::IVideoDriver> &driver,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);
            void add(std::shared_ptr<irr::video::IVideoDriver> &driver,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement, const std::map<std::string, std::string> info);
        private:
            std::map<std::string, indie::object::Form> _forms;
    };
}

#endif //__BOMBERMAN_FORMBANK_HPP__
