/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = CollisionSystem
 *
 * File creation = 11/06/2020
 * Last modification = 11/06/2020
 */

#ifndef __BOMBERMAN_COLLISIONSYSTEM_HPP__
#define __BOMBERMAN_COLLISIONSYSTEM_HPP__

#include "objects/StaticObject.hpp"
#include <list>
#include "objects/Player.hpp"

namespace indie::engine {
    class CollisionSystem {
        public:
            CollisionSystem();
            CollisionSystem(std::list<indie::object3D::StaticObject> &walls, indie::object3D::Player &player,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager);
            void drop(indie::object3D::Player &player);
            void create(std::list<indie::object3D::StaticObject> &walls, indie::object3D::Player &player,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager);
            inline bool empty() const { return _isEmpty; }
            void createBorder(std::list<indie::object3D::StaticObject> &walls, indie::object3D::Player &player,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager);

        private:
            irr::scene::IMetaTriangleSelector *_metaTriangle;
            bool _isEmpty;
    };
}

#endif //__BOMBERMAN_COLLISIONSYSTEM_HPP__
