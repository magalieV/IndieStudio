/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = StaticObject
 *
 * File creation = 08/06/2020
 * Last modification = 08/06/2020
 */

#ifndef __BOMBERMAN_STATICOBJECT_HPP__
#define __BOMBERMAN_STATICOBJECT_HPP__

#include <iostream>
#include <memory>
#include <vector3d.h>
#include <IVideoDriver.h>
#include <ISceneManager.h>
#include <IMeshSceneNode.h>

namespace indie::object3D {
    class StaticObject {
        public:
            StaticObject(const std::string &meshPath, const std::string &texturePath,
                const irr::core::vector3df &position,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                const std::shared_ptr<irr::video::IVideoDriver> &videoDriver);
            void setPosition(const irr::core::vector3df &position);
            [[nodiscard]] irr::core::vector3df getPosition() const;
            void setScale(const irr::core::vector3df &scaleCoeff);
            [[nodiscard]] irr::core::vector3df getScale() const;
            void setVisible(bool state);
            void setRotation(const irr::core::vector3df &rotation);
            [[nodiscard]] irr::scene::IMeshSceneNode *getScene() const;
            [[nodiscard]] irr::scene::IMesh *getMesh() const;
            void setAnimator(irr::scene::ISceneNodeAnimator *animator);
            irr::scene::ISceneNodeAnimator *getAnimator();
            irr::scene::ITriangleSelector *getSelector();
            void setSelector(irr::scene::ITriangleSelector *selector);
        private:
            irr::scene::IMeshSceneNode *_scene;
            irr::scene::IMesh *_mesh;
            irr::scene::ISceneNodeAnimator *_animator;
            irr::scene::ITriangleSelector *_selector;
    };
}

#endif //__BOMBERMAN_STATICOBJECT_HPP__
