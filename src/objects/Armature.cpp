/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Armature
 *
 * File creation = 06/06/2020
 * Last modification = 06/06/2020
 */

#include "objects/Armature.hpp"
#include "Engine/LoadError.hpp"

indie::object3D::Armature::Armature(const std::string &meshPath,
    const std::string &texturePath,
    const irr::core::vector3df &position,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    const std::shared_ptr<irr::video::IVideoDriver> &videoDriver)
{
    irr::io::path objectPath(meshPath.c_str());
    irr::io::path objectTexturePath(texturePath.c_str());

    _mesh = sceneManager->getMesh(objectPath);
    _scene = sceneManager->addAnimatedMeshSceneNode(_mesh);
    if (_scene) {
        _scene->setPosition(position);
        _scene->addShadowVolumeSceneNode();
        _scene->setMaterialTexture(0, videoDriver->getTexture(objectTexturePath));
        _scene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    } else {
        throw LoadError(CANT_OPEN(meshPath));
    }
}

irr::scene::IAnimatedMeshSceneNode *indie::object3D::Armature::getScene() const
{
    return _scene;
}

void indie::object3D::Armature::addAnimator(irr::scene::ISceneNodeAnimator *animator)
{
    _scene->addAnimator(animator);
}

void indie::object3D::Armature::setPosition(const irr::core::vector3df &position)
{
    _scene->setPosition(position);
}

irr::core::vector3df indie::object3D::Armature::getPosition() const
{
    return _scene->getPosition();
}

void indie::object3D::Armature::reiniRotation()
{
    _scene->setRotation({0, 0, 0});
}

void indie::object3D::Armature::setRotation(const indie::macro::MovementManager &move)
{
    switch (move) {
        case indie::macro::MovementManager::_LEFT:
            if (_scene->getRotation().Y + 10 > 360)
                _scene->setRotation({0, 0 + (10 - (360 - _scene->getRotation().Y)), 0});
            else
                _scene->setRotation({0, _scene->getRotation().Y + 10, 0});
            break;
        case indie::macro::MovementManager::_RIGHT:
            if (_scene->getRotation().Y - 10 < 0) {
                _scene->setRotation({0, 360 - (_scene->getRotation().Y - 10), 0});
            } else {
                _scene->setRotation({0, _scene->getRotation().Y - 10, 0});
            }
            break;
        default:
            break;
    }
}

irr::scene::IAnimatedMeshSceneNode *indie::object3D::Armature::getMesh() const
{
    return _scene;
}

void indie::object3D::Armature::standUp()
{
    if (_scene->getFrameNr() < 91 || _scene->getFrameNr() > 131) {
        _scene->setFrameLoop(91, 131);
        _scene->setAnimationSpeed(20);
    }
}

void indie::object3D::Armature::run()
{
    if (_scene->getFrameNr() < 1 || _scene->getFrameNr() > 81) {
        _scene->setFrameLoop(1, 81);
        _scene->setAnimationSpeed(100);
    }
}

void indie::object3D::Armature::jump()
{
    if (_scene->getFrameNr() < 141 || _scene->getFrameNr() > 161) {
        _scene->setFrameLoop(141, 161);
        _scene->setAnimationSpeed(30);
    }
}

void indie::object3D::Armature::setVisible(bool state)
{
    _scene->setVisible(state);
}

void indie::object3D::Armature::setRotation(const irr::core::vector3df &rotation)
{
    _scene->setRotation(rotation);
}

irr::core::vector3df indie::object3D::Armature::getRotation() const
{
    return _scene->getRotation();
}

void indie::object3D::Armature::dab() const
{
    if (_scene->getFrameNr() < 171 || _scene->getFrameNr() > 201) {
        _scene->setFrameLoop(171, 201);
        _scene->setAnimationSpeed(20);
    }
}

int indie::object3D::Armature::getActualFrameRate() const
{
    return _scene->getFrameNr();
}