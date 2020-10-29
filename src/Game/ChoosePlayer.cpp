/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = ChoosePlayer
 *
 * File creation = 07/06/2020
 * Last modification = 07/06/2020
 */

#include "Game/ChoosePlayer.hpp"
#include "Game/Game.hpp"
#include "Game/SplashScreen.hpp"

indie::game::ChoosePlayer::ChoosePlayer()
{
    _index = 0;
}

indie::game::ChoosePlayer::ChoosePlayer(
    std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerOne.b3d", "assets/game/player/PlayerColorSetOne.png", {0, 0, 0}, sceneManager, videoDriver));
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerTwo.b3d", "assets/game/player/PlayerColorSetTwo.png", {0, 0, 0}, sceneManager, videoDriver));
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerThree.b3d", "assets/game/player/PlayerColorSetThree.png", {0, 0, 0}, sceneManager, videoDriver));
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerFour.b3d", "assets/game/player/PlayerColorSetYellow.png", {0, 0, 0}, sceneManager, videoDriver));
    _camera = sceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 2, -5), irr::core::vector3df(0, 100, 200));
    _camera->setTarget(irr::core::vector3df(0,0,0));
    _index = 0;
    _buttonBank.addButton(indie::object::Button("OK", "Choose this player", indie::object::Button::info_t({800, 800, 1200, 998}, macro::_OK), guiEnvironnement, videoDriver));
    _objectBank.addObject(&_buttonBank);
    _text = indie::object::Text("Choose your player", irr::video::SColor(255, 255, 255, 255), {615, 100, 1000, 200}, guiEnvironnement);
    _objectBank.addObject(&_text);
}

void indie::game::ChoosePlayer::run(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    std::shared_ptr<irr::video::IVideoDriver> &videoDriver, indie::object::Window *device)
{
    indie::macro::ButtonSignal signal = indie::macro::ButtonSignal::_DEFAULT;
    float x = (float(1920 - device->getScreenSize().Width)) / 2.f;
    float y = (float(1080 - device->getScreenSize().Height)) / 2.f;
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    _pictureBank.add(indie::object::Picture("assets/game/player/choosePlayer.png", std::pair<float, float>(x * -1, y * -1), std::pair<float, float>(1920, 1080), videoDriver));
    for (auto &mesh : _playerChoice) {
        mesh->setVisible(false);
        mesh->standUp();
        mesh->setPosition({0, 0, -2});
    }
    _camera = sceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 2, -5), irr::core::vector3df(0, 100, 200));
    _camera->setTarget(irr::core::vector3df(0,0,0));
    _index = 0;
    _playerChoice.at(_index)->setVisible(true);

    while (device->isRunning()) {
        videoDriver->beginScene(true, true,
            irr::video::SColor(0,255,255,255));
        _pictureBank.draw(videoDriver);
        sceneManager->drawAll();
        _objectBank.draw(videoDriver);
        irr::EKEY_CODE keyPressed = device->getLastKeyPressed();
        signal = _buttonBank.handleEvent();
        if (signal != indie::macro::ButtonSignal::_DEFAULT)
            break;
        if (keyPressed == irr::KEY_LEFT)
                _playerChoice.at(_index)->setRotation(indie::macro::MovementManager::_LEFT);
        else if (keyPressed == irr::KEY_RIGHT)
                _playerChoice.at(_index)->setRotation(indie::macro::MovementManager::_RIGHT);
        else {
            irr::EKEY_CODE keyReleased = device->getLastKeyReleased();
            if (keyReleased == irr::KEY_UP) {
                _playerChoice.at(_index)->setVisible(false);
                _index = (_index >= 3) ? 0 : _index + 1;
                _playerChoice.at(_index)->setVisible(true);
                _playerChoice.at(_index)->reiniRotation();
            } else if (keyReleased == irr::KEY_DOWN) {
                _playerChoice.at(_index)->setVisible(false);
                _index = (_index <= 0) ? 3 : _index - 1;
                _playerChoice.at(_index)->setVisible(true);
                _playerChoice.at(_index)->reiniRotation();
            }
        }
        videoDriver->endScene();
    }
    if (signal == indie::macro::ButtonSignal::_OK) {
        indie::game::SplashScreen splash(videoDriver, sceneManager, device->getGuiEnvironement());
        splash.run(sceneManager, videoDriver, device);
        indie::game::CreateBoard board(videoDriver, sceneManager);
        indie::game::Game game(_playerChoice, _index, sceneManager, videoDriver, board, device->getGuiEnvironement());
        game.run(sceneManager, videoDriver, device);
    }
}