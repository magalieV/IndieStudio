/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = PowerUp
 *
 * File creation = 11/06/2020
 * Last modification = 11/06/2020
 */

#ifndef __BOMBERMAN_POWERUP_HPP__
#define __BOMBERMAN_POWERUP_HPP__

#include <iostream>
#include <vector3d.h>
#include <IVideoDriver.h>
#include <ISceneManager.h>
#include <memory>
#include "MacroIndie.hpp"
#include "objects/Player.hpp"
#include "IAnimatedMesh.h"

namespace indie::object3D {
    class PowerUp {
        public:
            PowerUp(const irr::core::vector3df &position,
                    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                    const std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                    indie::macro::PowerUpType type,
                    indie::object::Window *device);
            void setPosition(const irr::core::vector3df &position);
            [[nodiscard]] irr::core::vector3df getPosition() const;
            bool operator==(indie::macro::PowerUpType type);
            void interact(indie::object3D::Player &player, indie::object::Window *device);
            void update(indie::object::Window *device);
            bool isActive() const;
            void drop();
        private:
            irr::scene::IAnimatedMeshSceneNode *_scene;
            irr::scene::IAnimatedMesh *_mesh;
            indie::macro::PowerUpType _type;
            irr::u32 _timer;
            bool _isActive;
    };
}

#endif //__BOMBERMAN_POWERUP_HPP__
