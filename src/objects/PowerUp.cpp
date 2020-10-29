/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = PowerUp
 *
 * File creation = 11/06/2020
 * Last modification = 11/06/2020
 */

#include "objects/PowerUp.hpp"
#include <IAnimatedMeshSceneNode.h>
#include "Engine/LoadError.hpp"

indie::object3D::PowerUp::PowerUp(const irr::core::vector3df &position,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    const std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
    indie::macro::PowerUpType type,
    indie::object::Window *device)
{
    irr::io::path objectPath("assets/game/powerUp/PowerUps.b3d");
    irr::io::path objectTexturePath;

    _mesh = sceneManager->getMesh(objectPath);
    _scene = sceneManager->addAnimatedMeshSceneNode(_mesh);
    _type = type;
    _isActive = true;
    _timer = device->getTime();
    switch (_type) {
        case indie::macro::PowerUpType::_BOMB_UP:
            objectTexturePath = "assets/game/powerUp/bombBonus.png";
            break;
        case indie::macro::PowerUpType::_BOMB_DOWN:
            objectTexturePath = "assets/game/powerUp/bombMalus.png";
            break;
        default:
            objectTexturePath = "assets/game/powerUp/Invincible.png";
            break;
    }
    if (_scene) {
        _scene->setPosition(position);
        _scene->addShadowVolumeSceneNode();
        _scene->setMaterialTexture(0, videoDriver->getTexture(objectTexturePath));
        _scene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    } else {
        throw LoadError(CANT_OPEN(std::string(objectTexturePath.c_str())));
    }
    irr::scene::ISceneNodeAnimator* ani=sceneManager->createRotationAnimator(irr::core::vector3df(0,1,0));
    _scene->addAnimator(ani);
    ani->drop();
}

void indie::object3D::PowerUp::setPosition(const irr::core::vector3df &position)
{
    _scene->setPosition(position);
}

irr::core::vector3df indie::object3D::PowerUp::getPosition() const
{
    return _scene->getPosition();
}

bool indie::object3D::PowerUp::operator==(indie::macro::PowerUpType type)
{
    return _type == type;
}

void indie::object3D::PowerUp::interact(indie::object3D::Player &player, indie::object::Window *device)
{
    irr::core::aabbox3d<irr::f32> powerUpBox = _scene->getTransformedBoundingBox();
    irr::core::aabbox3d<irr::f32> playerBox = player.getMesh()->getTransformedBoundingBox();

    if (!_isActive || player.isDie())
        return;
    powerUpBox.MaxEdge.X -= 0.2f;
    powerUpBox.MaxEdge.Z += 0.2f;
    if (playerBox.intersectsWithBox(powerUpBox)) {
        player.setEffect(_type, device);
        _isActive = false;
        _scene->setVisible(false);
    }
}

void indie::object3D::PowerUp::update(indie::object::Window *device)
{
    auto timePassed = device->getTime();
    const irr::f32 framerate = (irr::f32)(timePassed - _timer) / 1000.f;

    if (framerate > 6) {
        _isActive = false;
        _scene->setVisible(false);
    }
}

bool indie::object3D::PowerUp::isActive() const
{
    return _isActive;
}

void indie::object3D::PowerUp::drop()
{
    _isActive = false;
    _scene->setVisible(false);
    _scene->removeAnimators();
    _scene->remove();
}