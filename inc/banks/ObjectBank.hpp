/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = ObjectBank
 *
 * File creation = 03/06/2020
 * Last modification = 03/06/2020
 */

#ifndef __BOMBERMAN_OBJECTBANK_HPP__
#define __BOMBERMAN_OBJECTBANK_HPP__

#include "interface/IVisualObject.hpp"
#include <memory>
#include <list>
#include <chrono>

namespace indie::bank {
    class ObjectBank {
        public:
            ObjectBank() = default;
            void addObject(indie::object::IVisualObject *object);
            void draw(std::shared_ptr<irr::video::IVideoDriver> &driver);

        private:
            std::list<indie::object::IVisualObject *> _objectList;
            std::chrono::time_point<std::chrono::system_clock> _lastTimer;
    };
}

#endif //__BOMBERMAN_OBJECTBANK_HPP__
