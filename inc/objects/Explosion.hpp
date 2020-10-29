/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Explosion
 *
 * File creation = 11/06/2020
 * Last modification = 11/06/2020
 */

#ifndef __BOMBERMAN_EXPLOSION_HPP__
#define __BOMBERMAN_EXPLOSION_HPP__

#include <IAnimatedMesh.h>
#include <IAnimatedMeshSceneNode.h>
#include <memory>
#include <IParticleAnimatedMeshSceneNodeEmitter.h>
#include <IParticleSystemSceneNode.h>
#include "Engine/Window.hpp"
#include "objects/Sound.hpp"

namespace indie::object3D {
    class Explosion {
        public:
            Explosion() = delete;
            Explosion(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                const std::shared_ptr<irr::video::IVideoDriver> &videoDriver);
            void setPosition(irr::core::vector3df pos);
            void startTimer();
            void update();
            void setVisible(bool state);
            [[nodiscard]] bool isEnd() const;
            [[nodiscard]] irr::core::vector3df getPosition() const;
            irr::scene::IAnimatedMeshSceneNode *getScene() const;
        private:
            irr::scene::IAnimatedMesh *_mesh;
            irr::scene::IAnimatedMeshSceneNode *_scene;
            irr::scene::IParticleAnimatedMeshSceneNodeEmitter *_particule;
            irr::scene::IParticleSystemSceneNode *part;
            float _actual_size;
            float _baseHeight;
            float _finalHeight;
            float _loopTime;
            float _timer;
            float frameRate;
            bool _endAnim;
            bool _startTimer;
            indie::object::Sound _sound;
    };
}

#endif //__BOMBERMAN_EXPLOSION_HPP__
