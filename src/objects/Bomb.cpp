/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Bomb
 *
 * File creation = 11/06/2020
 * Last modification = 11/06/2020
 */

#include "objects/Bomb.hpp"
#include "Engine/LoadError.hpp"

indie::object3D::Bomb::Bomb(float timer, indie::object::Window *device,
    irr::u32 framerate,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    const std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
    unsigned int sizeExplode)
{
    _sizeExplode = sizeExplode;
    _mesh = sceneManager->getMesh("assets/game/bomb/bomb.b3d");
    _scene = sceneManager->addAnimatedMeshSceneNode(_mesh);
    if (_scene) {
        _scene->setPosition({0, 0, 0});
        _scene->addShadowVolumeSceneNode();
        _scene->setMaterialTexture(0, videoDriver->getTexture("assets/game/bomb/Bomb.TGA"));
        _scene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    } else {
        throw LoadError(CANT_OPEN("bomb"));
    }
    _scene->setAnimationSpeed(framerate);
    _startTimerTime = device->getTime();
    _startExplode = false;
    _timer = timer;
    for (unsigned int index = 0; index < (sizeExplode * 4) + 1; index++)
        _explosion.emplace_back(indie::object3D::Explosion(sceneManager, videoDriver));
    std::vector<float> moove = {1.f, 0.f, 0.f, 1.f, -1.f, 0.f, 0.f, -1.f};
    unsigned int counter = 0;
    unsigned int coeff = 1;
    unsigned int idx = 0;
    irr::core::vector3df pos = _scene->getPosition();
    for (unsigned int index = 1; index < _explosion.size(); index++) {
        pos = _scene->getPosition();
        pos.X += moove.at(idx) * coeff;
        pos.Z += moove.at(idx + 1) * coeff;
        idx += 2;
        _explosion.at(index).setPosition(pos);
        _bombPos.emplace_back(pos);
        counter++;
        if (counter >= 4) {
            coeff += 1;
            idx = 0;
            counter = 0;
        }
    }
}

void indie::object3D::Bomb::update(indie::object::Window *device, const std::vector<std::string> &map)
{
    auto timePassed = device->getTime();
    const irr::f32 framerate = (irr::f32)(timePassed - _startTimerTime) / 1000.f;

    if (framerate > _timer && !_startExplode) {
        _scene->setVisible(false);
        for (auto &explosion : _explosion) {
            if (map.at(explosion.getPosition().Z * -1).at(explosion.getPosition().X) != 'X')
                explosion.startTimer();
            else
                explosion.setVisible(false);
        }
        _startExplode = true;
    }
    if (_startExplode) {
        for (auto &explosion : _explosion)
            explosion.update();
    }
}

void indie::object3D::Bomb::setPosition(const irr::core::vector3df &posi, const std::vector<std::string> &map)
{
    _scene->setPosition(posi);
    _explosion.at(0).setPosition(posi);
    _bombPos.clear();
    std::vector<float> moove = {1.f, 0.f, 0.f, 1.f, -1.f, 0.f, 0.f, -1.f};
    unsigned int counter = 0;
    unsigned int coeff = 1;
    unsigned int idx = 0;
    irr::core::vector3df pos = _scene->getPosition();
    for (unsigned int index = 1; index < _explosion.size(); index++) {
        pos = _scene->getPosition();
        pos.X += moove.at(idx) * coeff;
        pos.Z += moove.at(idx + 1) * coeff;
        idx += 2;
        if (map.at(pos.Z * -1).at(pos.X) != 'X') {
            _bombPos.emplace_back(irr::core::vector3df(pos.X, 0 ,pos.Z));
        }
        _explosion.at(index).setPosition(pos);
        counter++;
        if (counter >= 4) {
            coeff += 1;
            idx = 0;
        }
    }
}

void indie::object3D::Bomb::setVisible(bool state)
{
    _scene->setVisible(state);
    for (auto &explosion : _explosion)
        explosion.setVisible(state);
}

bool indie::object3D::Bomb::isEnd() const
{
    return _startExplode;
}

bool indie::object3D::Bomb::isVisible() const
{
    return _scene->isVisible();
}

std::vector<irr::core::vector3df> indie::object3D::Bomb::bombPosition() const
{
    return _bombPos;
}

bool indie::object3D::Bomb::explosionHit(const irr::core::vector3df &position)
{
    irr::core::vector3df newPos;

    if (_startExplode) {
        for (auto &explosion : _explosion) {
            int intPartX = int(position.X);
            int intPartZ = int(position.Z);
            if (intPartX < 0)
                intPartX = 1;
            if (intPartZ > -1)
                intPartZ = -1;
            if (intPartX + 0.5 < position.X)
                intPartX += 1;
            if (intPartZ - 0.5 > position.Z)
                intPartZ -= 1;
            newPos = explosion.getPosition();
            if (!explosion.isEnd() && newPos.X == float(intPartX) && newPos.Z == float(intPartZ))
                return true;
        }
    }
    return false;
}

void indie::object3D::Bomb::drop()
{
    setVisible(false);
    _startExplode = false;
    for (auto &explosion : _explosion) {
        explosion.setVisible(false);
    }
}