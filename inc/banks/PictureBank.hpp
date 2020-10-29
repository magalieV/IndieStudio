/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = PictureBank
 *
 * File creation = 04/06/2020
 * Last modification = 04/06/2020
 */

#ifndef __BOMBERMAN_PICTUREBANK_HPP__
#define __BOMBERMAN_PICTUREBANK_HPP__

#include <list>
#include "interface/IVisualObject.hpp"
#include "objects/Picture.hpp"
#include <map>

namespace indie::bank {
    class PictureBank : public indie::object::IVisualObject {
        public:
            PictureBank() = default;
            ~PictureBank() = default;
            void draw(std::shared_ptr<irr::video::IVideoDriver> &driver) final;
            void add(indie::object::Picture button);
            void add(const std::string &configFile, std::shared_ptr<irr::video::IVideoDriver> &driver,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);
            void add(std::shared_ptr<irr::video::IVideoDriver> &driver,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
                const std::map<std::string, std::string> info);

        private:
            std::list<indie::object::Picture> _pictureList;
    };
}

#endif //__BOMBERMAN_PICTUREBANK_HPP__
