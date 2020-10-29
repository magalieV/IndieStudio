/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Armature
 *
 * File creation = 06/06/2020
 * Last modification = 06/06/2020
 */

#ifndef __BOMBERMAN_ARMATURE_HPP__
#define __BOMBERMAN_ARMATURE_HPP__

#include <iostream>
#include <vector3d.h>
#include <IAnimatedMeshSceneNode.h>
#include <ISceneManager.h>
#include "MacroIndie.hpp"
#include <memory>

namespace indie::object3D {
    class Armature {
        public:
            Armature() = default;
            Armature(const std::string &meshPath, const std::string &texturePath,
                const irr::core::vector3df &position,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                const std::shared_ptr<irr::video::IVideoDriver> &videoDriver);
            void setPosition(const irr::core::vector3df &position);
            void setRotation(const indie::macro::MovementManager &move);
            void setRotation(const irr::core::vector3df &rotation);
            [[nodiscard]] irr::core::vector3df getRotation() const;
            [[nodiscard]] irr::scene::IAnimatedMeshSceneNode *getMesh() const;
            void standUp();
            void run();
            void jump();
            [[nodiscard]] irr::core::vector3df getPosition() const;
            void setVisible(bool state);
            void reiniRotation();
            [[nodiscard]] irr::scene::IAnimatedMeshSceneNode *getScene() const;
            void addAnimator(irr::scene::ISceneNodeAnimator *animator);
            void dab() const;
            int getActualFrameRate() const;

        private:
            irr::scene::IAnimatedMeshSceneNode *_scene;
            irr::scene::IAnimatedMesh *_mesh;
    };
}

#endif //__BOMBERMAN_ARMATURE_HPP__
