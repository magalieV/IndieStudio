/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = IA
 *
 * File creation = 12/06/2020
 * Last modification = 12/06/2020
 */

#ifndef __BOMBERMAN_IA_HPP__
#define __BOMBERMAN_IA_HPP__

#include "Engine/Window.hpp"
#include "Armature.hpp"
#include "Engine/PathFinder.hpp"
#include "objects/Player.hpp"

namespace indie::engine{
    class CollisionSystem;
}

namespace indie::object3D {
    class IA : public indie::object3D::Player {
        public:
            IA(indie::object3D::Armature *armature);
            IA() = default;
            IA& operator=(const IA &other);
            std::vector<std::string> update(indie::object3D::Player player, indie::object::Window *device,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                const std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                std::vector<std::string> &map,
                std::list<indie::object3D::StaticObject> &wall,
                indie::engine::CollisionSystem &collision);
        private:
            indie::engine::PathFinder _pathFinder;
            std::pair<int, int> _goal;
            indie::macro::MovementManager _lastMovement;
            bool _bombPos;
            std::pair<int, int> _safePos;
            irr::u32 _timeMove;
    };
}

#endif //__BOMBERMAN_IA_HPP__
