/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Intro
 *
 * File creation = 10/06/2020
 * Last modification = 10/06/2020
 */

#include "Game/Intro.hpp"

indie::game::Intro::Intro(
    std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement) :
    _indieName("assets/name.obj", "", {0, 0, 0}, sceneManager, videoDriver)
{
    _indieName.setScale({3, 3, 3});
    _camera = sceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 10, 15), irr::core::vector3df(0, 100, 200));
    _camera->setTarget(irr::core::vector3df(0,0,0));
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerTwo.b3d", "assets/game/player/PlayerColorSetTwo.png", {4, 0, 1}, sceneManager, videoDriver));
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerOne.b3d", "assets/game/player/PlayerColorSetOne.png", {2, 0, 1}, sceneManager, videoDriver));
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerThree.b3d", "assets/game/player/PlayerColorSetThree.png", {-2, 0, 1}, sceneManager, videoDriver));
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerFour.b3d", "assets/game/player/PlayerColorSetYellow.png", {-4, 0, 1}, sceneManager, videoDriver));
    for (auto &play : _playerChoice) {
        _allPlayer.emplace_back(indie::object3D::Player(play));
        play->standUp();
        irr::core::vector3df rota = play->getRotation();
        rota.Y = 180;
        play->setRotation(rota);
    }
}

void indie::game::Intro::run(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager, std::shared_ptr<irr::video::IVideoDriver> &videoDriver, indie::object::Window *device)
{
    auto _lastTimer = std::chrono::system_clock::now();
    bool dab = false;
    auto startDab = std::chrono::system_clock::now();
    bool mustMove = true;
    bool mustStop = false;
    irr::u32 timeBefore = device->getTime();
    irr::u32 timeNow = device->getTime();

    while (device->isRunning()) {
        videoDriver->beginScene(true, true,
                                irr::video::SColor(255, 0, 0, 0));
        auto timer = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = timer - _lastTimer;

        while (elapsed_seconds.count() < 0.020) {
            timer = std::chrono::system_clock::now();
            elapsed_seconds = timer - _lastTimer;
        }
        sceneManager->drawAll();
        irr::core::vector3df camPos = _camera->getPosition();
        timeNow = device->getTime();
        const irr::f32 framerate = (irr::f32)(timeNow - timeBefore) / 1000.f;
        timeBefore = timeNow;
        if (camPos.Y - 0.003 < 5) {
            for (unsigned int index = 0; index < _allPlayer.size(); index++) {
                irr::core::vector3df pos = _allPlayer.at(index).getPosition();
                auto actualTime = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsedTime = actualTime - startDab;
                if (dab && index == 1 && elapsedTime.count() > 1.5) {
                    mustMove = true;
                }
                if (index == 1 && pos.Z > 6 && (!mustMove || !dab)) {
                    _allPlayer.at(index).dab();
                    if (!dab)
                        startDab = std::chrono::system_clock::now();
                    dab = true;
                    mustMove = false;
                } else {
                    pos.Z += (framerate + 0.01);
                    _allPlayer.at(index).setPosition(pos);
                    _allPlayer.at(index).run();
                }
                if (_allPlayer.at(1).getPosition().Z > 21)
                    mustStop = true;
            }
        } else {
            camPos.Y -= (framerate * 1.1f);
            _camera->setPosition(camPos);
        }
        videoDriver->endScene();
        if (device->_eventHandler->isKeyPressed(irr::KEY_SPACE))
            break;
        if (mustStop)
            break;
    }
    for (auto &play : _playerChoice) {
        play->setVisible(false);
    }
    _indieName.setVisible(false);
}