/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Explosion
 *
 * File creation = 11/06/2020
 * Last modification = 11/06/2020
 */

#include "objects/Explosion.hpp"
#include "Engine/LoadError.hpp"

indie::object3D::Explosion::Explosion(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    const std::shared_ptr<irr::video::IVideoDriver> &videoDriver) : _sound("assets/game/explode.ogg")
{
    _mesh = sceneManager->getMesh("assets/game/bomb/TMPMiniBlock.3ds");
    _scene = sceneManager->addAnimatedMeshSceneNode(_mesh);
    if (_scene) {
        _scene->setPosition({0, 0, 0});
        _scene->addShadowVolumeSceneNode();
        _scene->setMaterialTexture(0, videoDriver->getTexture("assets/game/bomb/TMPFlame.png"));
        _scene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    } else {
        throw LoadError(CANT_OPEN("explosion"));
    }
    _scene->setAnimationSpeed(80);
    part = sceneManager->addParticleSystemSceneNode(false);
    _timer = 0.8f;
    _particule = part->createAnimatedMeshSceneNodeEmitter(_scene, false,irr::core::vector3df(0.01f, 0.01f, 0.0f),
        100.0f, -1, false,80, 100,
        irr::video::SColor(255, 235, 129, 33),irr::video::SColor(255, 255, 236, 0),
        1000, 1500, 360,irr::core::dimension2df(0.15f, 0.15f),irr::core::dimension2df(0.15f, 0.15f));
    _actual_size = 0.16f;
    _baseHeight = 0.15f;
    _finalHeight = 0.7f;
    _loopTime = 0.4f;
    if (_particule) {
        part->setEmitter(_particule);
        irr::scene::IParticleAffector *paf = part->createFadeOutParticleAffector();
        part->addAffector(paf);
        part->setMaterialFlag(irr::video::EMF_LIGHTING,false);
        part->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
        part->setMaterialTexture(0, videoDriver->getTexture("assets/game/bomb/BrightFire.png"));
        part->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
        part->setPosition(irr::core::vector3df(_scene->getPosition().X,_scene->getPosition().Y + 0.5f, _scene->getPosition().Z));
        part->setScale(irr::core::vector3df(0.047f, 0.0065f, 0.1f));
    }
    _scene->setVisible(false);
    part->setVisible(false);
    _startTimer = false;
    _endAnim = false;
    frameRate = 0.006f;
}

void indie::object3D::Explosion::setPosition(irr::core::vector3df pos)
{
    _scene->setPosition(pos);
    pos.Y += 0.5f;
    part->setPosition(pos);
}

void indie::object3D::Explosion::startTimer()
{
    _startTimer = true;
    part->setVisible(true);
    _scene->setVisible(true);
    _sound.play();
    _sound.setVolume(100);
}

void indie::object3D::Explosion::update()
{
    if (!_startTimer) {
        return;
    }
    if (_timer < 0) {
        _startTimer = false;
        _scene->setVisible(false);
        _endAnim = true;
        _sound.stop();
        part->setVisible(false);
        return;
    }
    _timer -= frameRate;
    if (_timer < 0.7f)
        _particule->setDirection(irr::core::vector3df(0.0001f, 0.0001f, 0.0f));
    if (_timer > 0.35f) {
        _actual_size += ((_finalHeight - _baseHeight) / (_loopTime / 2.0f)) * (frameRate * 1.2f);
        _particule->setMinStartSize(irr::core::dimension2d<irr::f32>(_actual_size, _actual_size));
        _particule->setMaxStartSize(irr::core::dimension2d<irr::f32>(_actual_size, _actual_size));
    }
}

void indie::object3D::Explosion::setVisible(bool state)
{
    _startTimer = state;
    _scene->setVisible(state);
    part->setVisible(state);
    _endAnim = true;
}

bool indie::object3D::Explosion::isEnd() const
{
    return _endAnim;
}

irr::core::vector3df indie::object3D::Explosion::getPosition() const
{
    return _scene->getPosition();
}

irr::scene::IAnimatedMeshSceneNode * indie::object3D::Explosion::getScene() const
{
    return _scene;
}