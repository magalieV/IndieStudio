/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Bomb
 *
 * File creation = 11/06/2020
 * Last modification = 11/06/2020
 */

#ifndef __BOMBERMAN_BOMB_HPP__
#define __BOMBERMAN_BOMB_HPP__

#include "Engine/Window.hpp"
#include "Explosion.hpp"
#include <vector>

namespace indie::object3D {
    class Bomb {
        public:
            Bomb() = delete;
            Bomb(float timer, indie::object::Window *device, irr::u32 framerate,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                const std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                unsigned int sizeExplode = 1);
            void update(indie::object::Window *device,  const std::vector<std::string> &map);
            void setPosition(const irr::core::vector3df &pos, const std::vector<std::string> &map);
            void setVisible(bool state);
            [[nodiscard]] bool isEnd() const;
            [[nodiscard]] bool isVisible() const;
            void drop();
            bool explosionHit(const irr::core::vector3df &position);
            [[nodiscard]] std::vector<irr::core::vector3df> bombPosition() const;
        private:
            irr::scene::IAnimatedMesh *_mesh;
            irr::scene::IAnimatedMeshSceneNode *_scene;
            float _timer;
            irr::u32 _startTimerTime;
            std::vector<indie::object3D::Explosion> _explosion;
            bool _startExplode;
            unsigned int _sizeExplode;
            std::vector<irr::core::vector3df> _bombPos;
    };
}

#endif //__BOMBERMAN_BOMB_HPP__
