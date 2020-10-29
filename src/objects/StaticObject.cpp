/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = StaticObject
 *
 * File creation = 08/06/2020
 * Last modification = 08/06/2020
 */

#include "objects/StaticObject.hpp"
#include "Engine/LoadError.hpp"

indie::object3D::StaticObject::StaticObject(const std::string &meshPath,
    const std::string &texturePath,
    const irr::core::vector3df &position,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    const std::shared_ptr<irr::video::IVideoDriver> &videoDriver)
{
    irr::io::path objectPath(meshPath.c_str());
    irr::io::path objectTexturePath(texturePath.c_str());

    _mesh = sceneManager->getMesh(objectPath);
    _scene = sceneManager->addOctreeSceneNode(_mesh);
    if (_scene) {
        _scene->setPosition(position);
        _scene->addShadowVolumeSceneNode();
        if (!objectTexturePath.empty())
            _scene->setMaterialTexture(0, videoDriver->getTexture(objectTexturePath));
        _scene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    } else {
        throw LoadError(CANT_OPEN(meshPath));
    }
    _animator = nullptr;
    _selector = nullptr;
}

irr::scene::IMeshSceneNode * indie::object3D::StaticObject::getScene() const
{
    return _scene;
}

void indie::object3D::StaticObject::setPosition(
    const irr::core::vector3df &position)
{
    _scene->setPosition(position);
}

void indie::object3D::StaticObject::setVisible(bool state)
{
    _scene->setVisible(state);
}

void indie::object3D::StaticObject::setScale(const irr::core::vector3df &scaleCoeff)
{
    _scene->setScale(scaleCoeff);
}

irr::core::vector3df indie::object3D::StaticObject::getScale() const
{
    return _scene->getScale();
}

void indie::object3D::StaticObject::setRotation(const irr::core::vector3df &rotation)
{
    _scene->setRotation(rotation);
}

irr::scene::IMesh * indie::object3D::StaticObject::getMesh() const
{
    return _mesh;
}

irr::core::vector3df indie::object3D::StaticObject::getPosition() const
{
    return _scene->getPosition();
}

irr::scene::ISceneNodeAnimator * indie::object3D::StaticObject::getAnimator()
{
    return _animator;
}

void indie::object3D::StaticObject::setAnimator(irr::scene::ISceneNodeAnimator *animator)
{
    if (_animator)
        _animator->drop();
    _animator = animator;
}

void indie::object3D::StaticObject::setSelector(irr::scene::ITriangleSelector *selector)
{
    _selector = selector;
}

irr::scene::ITriangleSelector * indie::object3D::StaticObject::getSelector()
{
    return _selector;
}