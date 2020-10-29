/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Game
 *
 * File creation = 10/06/2020
 * Last modification = 10/06/2020
 */

#include "Game/Game.hpp"
#include "MacroIndie.hpp"
#include "objects/PowerUp.hpp"
#include "objects/Text.hpp"
#include <fstream>
#include "../EncryptTool/inc/XMLReader.hpp"
#include "../EncryptTool/inc/Encryption.hpp"
#include "../EncryptTool/inc/Decryption.hpp"

indie::game::Game::Game(std::vector<indie::object3D::Armature *> _allNpc,
    unsigned int actualNpc,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    std::shared_ptr<irr::video::IVideoDriver> videoDriver,
    indie::game::CreateBoard &board, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement) :
    _board(board), _pause(new indie::game::Pause(sceneManager, videoDriver, guiEnvironnement)), _endGame(new indie::game::EndGame(sceneManager, videoDriver, guiEnvironnement))
{
    _player = new indie::object3D::Player(_allNpc.at(actualNpc));
    _background = indie::object::Picture("assets/game/game_back.png",
                                         std::pair<float, float>(0, 0),
                                         std::pair<float, float>(1920, 1080),
                                         videoDriver);
    _pictureBank.add(indie::object::Picture(
        "assets/game/game_object/player" + std::to_string(actualNpc + 1) +
        ".png", std::pair<float, float>(0, 100),
        std::pair<float, float>(330, 200), videoDriver));
    _pictureBank.add(indie::object::Picture("assets/game/game_object/bomb.png",
                                            std::pair<float, float>(0, 300),
                                            std::pair<float, float>(50, 48),
                                            videoDriver));
    _objectBank.addObject(&_pictureBank);
    _player->setPosition({1, 0, -1});
    _player->reiniRotation();
    _camera = sceneManager->addCameraSceneNode(nullptr, irr::core::vector3df(
        BOARD_SIZE / 2, 13, -BOARD_SIZE / 3 * 2), irr::core::vector3df(0, 100,
                                                                       200));
    _camera->setTarget(
        irr::core::vector3df(BOARD_SIZE / 2, 0, -BOARD_SIZE / 2));
    _collision.create(_board.getWall(), *_player, sceneManager);
    _playerIndex = actualNpc;
    for (unsigned int index = 0; index < _allNpc.size(); index++) {
        if (index != actualNpc) {
            _ia.push_back(new indie::object3D::IA(_allNpc.at(index)));
            _ia.back()->setVisible(true);
        }
    }
    std::vector<float> npcPos = {1.f, BOARD_SIZE - 2, BOARD_SIZE - 2, 1.f,
                                 BOARD_SIZE - 2, BOARD_SIZE - 2};
    unsigned int counter = 0;
    for (auto ia : _ia) {
        ia->setPosition(
            {npcPos.at(counter), 0.f, npcPos.at(counter + 1) * -1.f});
        counter += 2;
    }
    _playerChoice = std::move(_allNpc);
    for (auto ia : _ia) {
        _collisionIA.emplace_back(indie::engine::CollisionSystem());
        _collisionIA.back().create(_board.getWall(), *ia, sceneManager);
    }
}

void indie::game::Game::loadGame(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager, std::shared_ptr<irr::video::IVideoDriver> videoDriver, indie::object::Window *device,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    std::list<std::string> content = encrypt::Decryption::stringFromFile(".save/.users/." + device->getUserName() + "_save/.usersave.xml");
    std::list<std::vector<std::string> > userList = XMLReader::getGroup("<gameSave>", "</gameSave>", content);
    std::vector<std::string> map;
    std::string mapTmp;
    bool isInvincible = false;
    unsigned int bombCounter = 0;
    std::string position;
    unsigned int score = 0;
    int iaNumber = 0;

    _pause = new indie::game::Pause(sceneManager, videoDriver, guiEnvironnement);
    _endGame = new indie::game::EndGame(sceneManager, videoDriver, guiEnvironnement);
    for (const auto &value : userList) {
        if (value[0] == "playerIndex") {
            _playerIndex = std::atoi(value[1].c_str());
        } else if (value[0] == "map")
            mapTmp = value[1];
        else if (value[0] == "Invincible") {
            isInvincible = std::atoi(value[1].c_str());
        } else if (value[0] == "BombCounter") {
            bombCounter = std::atoi(value[1].c_str());
        } else if (value[0] == "PlayerPosition") {
            position = value[1];
        } else if (value[0] == "Score") {
            score = std::atoi(value[1].c_str());
        } else if (value[0] == "IaNumber") {
            iaNumber = std::atoi(value[1].c_str());
        }
    }
    _background = indie::object::Picture("assets/game/game_back.png", std::pair<float, float>(0, 0), std::pair<float, float>(1920, 1080), videoDriver);
    _pictureBank.add(indie::object::Picture("assets/game/game_object/player" + std::to_string(_playerIndex + 1) + ".png", std::pair<float, float>(0, 100), std::pair<float, float>(330, 200), videoDriver));
    _pictureBank.add(indie::object::Picture("assets/game/game_object/bomb.png", std::pair<float, float>(0, 300), std::pair<float, float>(50, 48), videoDriver));
    _objectBank.addObject(&_pictureBank);
    std::vector<std::string> tmp = XMLReader::splitString(";", position);
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerOne.b3d", "assets/game/player/PlayerColorSetOne.png", {0, 0, 0}, sceneManager, videoDriver));
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerTwo.b3d", "assets/game/player/PlayerColorSetTwo.png", {0, 0, 0}, sceneManager, videoDriver));
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerThree.b3d", "assets/game/player/PlayerColorSetThree.png", {0, 0, 0}, sceneManager, videoDriver));
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerFour.b3d", "assets/game/player/PlayerColorSetYellow.png", {0, 0, 0}, sceneManager, videoDriver));
    _player = new indie::object3D::Player(_playerChoice.at(_playerIndex));
    _player->setPosition({std::stof(tmp.at(0)), std::stof(tmp.at(1)), std::stof(tmp.at(2))});
    _player->invincible(isInvincible, device);
    _player->setNumberOfBomb(bombCounter);
    _player->setScore(score);
    std::string str;
    unsigned int counter = 0;
    for (auto &c : mapTmp) {
        if (counter == BOARD_SIZE) {
            map.emplace_back(str);
            str.clear();
            counter = 0;
        }
        str.push_back(c);
        counter++;
    }
    if (!str.empty())
        map.emplace_back(str);
    _board = indie::game::CreateBoard(videoDriver, sceneManager, map);
    _player->setPosition({1, 0, -1});
    _player->reiniRotation();
    _camera = sceneManager->addCameraSceneNode(nullptr, irr::core::vector3df(BOARD_SIZE/2, 13, -BOARD_SIZE/3 * 2), irr::core::vector3df(0, 100, 200));
    _camera->setTarget(irr::core::vector3df(BOARD_SIZE/2,0,-BOARD_SIZE/2));
    _collision.create(_board.getWall(), *_player, sceneManager);
    int iaCounter = 0;
    for (unsigned int index = 0; index < _playerChoice.size(); index++) {
        if (index != _playerIndex) {
            iaCounter++;
            _ia.push_back(new indie::object3D::IA(_playerChoice.at(index)));
            _ia.back()->setVisible(true);
            if (iaCounter > iaNumber) {
                _playerChoice.at(index)->setVisible(false);
                _ia.back()->setDie();
            }
        }
    }
    std::vector<float> npcPos = {1.f, BOARD_SIZE - 2, BOARD_SIZE - 2, 1.f, BOARD_SIZE - 2, BOARD_SIZE - 2};
    unsigned int idx = 0;
    for (auto ia : _ia) {
        ia->setPosition({npcPos.at(idx), 0.f, npcPos.at(idx + 1) * -1.f});
        idx += 2;
    }
    for (auto ia : _ia) {
        _collisionIA.emplace_back(indie::engine::CollisionSystem());
        _collisionIA.back().create(_board.getWall(), *ia, sceneManager);
    }
}

void indie::game::Game::reset(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager, std::shared_ptr<irr::video::IVideoDriver> videoDriver, indie::object::Window *device, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    _player->setNumberOfBomb(5);
    _player->setScore(0);
    _player->invincible(false, device);
    _player->setPosition({1, 0, -1});
    _player->reiniRotation();
    _player->reset();
    int idx = 0;
    indie::engine::GenerateMap generator;
    _board.drop();
    _board = indie::game::CreateBoard(videoDriver, sceneManager, generator.generate());
    _collision.drop(*_player);
    _collision.create(_board.getWall(), *_player, sceneManager);
    for (auto &ia : _ia) {
        _collisionIA.at(idx).drop(*ia);
        _collisionIA.at(idx).create(_board.getWall(), *ia,
                                    sceneManager);
        idx++;
    }
    std::vector<float> npcPos = {1.f, BOARD_SIZE - 2, BOARD_SIZE - 2, 1.f, BOARD_SIZE - 2, BOARD_SIZE - 2};
    idx = 0;
    for (auto ia : _ia) {
        ia->setPosition({npcPos.at(idx), 0.f, npcPos.at(idx + 1) * -1.f});
        idx += 2;
        ia->setVisible(true);
        ia->reset();
    }
}

void indie::game::Game::run(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager, std::shared_ptr<irr::video::IVideoDriver> &videoDriver, indie::object::Window *device)
{
    _player->resetTime(device->getTime());
    for (auto &ia : _ia) {
        ia->resetTime(device->getTime());
    }
    std::vector<std::string> map = _board.getMap();
    int randValue;
    std::list<indie::object3D::PowerUp> _powersUp;
    std::string tmp;
    bool pauseMenu = false;
    indie::macro::ButtonSignal signal = indie::macro::ButtonSignal::_DEFAULT;
    std::vector<std::string> tmpMap = map;
    bool endGame = false;
    bool lost = false;
    indie::object::Text bombNumber(std::to_string(_player->getbombNumber()), irr::video::SColor(255, 255, 255, 255), irr::core::rect<irr::s32>(50, 300, 80, 300), device->getGuiEnvironement());
    indie::object::Text scorePlayer("Score: " + std::to_string(_player->getScore()), irr::video::SColor(255, 255, 255, 255), irr::core::rect<irr::s32>(100, 300, 180, 300), device->getGuiEnvironement());

    while (device->isRunning()) {
        videoDriver->beginScene(true, true,
                                irr::video::SColor(0, 255, 255, 255));
        _background.draw(videoDriver);
        sceneManager->drawAll();
        _objectBank.draw(videoDriver);
        bombNumber.setText(std::to_string(_player->getbombNumber()));
        scorePlayer.setText("Score: " + std::to_string(_player->getScore()));
        bombNumber.draw(videoDriver);
        scorePlayer.draw(videoDriver);
        if (!pauseMenu) {
            _player->moovePlayer(device);
            tmpMap = map;
            map = _player->update(device, sceneManager, videoDriver, map,
                                  _board.getWall(), _collision);
            _board.setMap(map);
            std::list<irr::core::vector3df> walls = _player->getLastDeleteWall();
            for (const auto &pos : walls) {
                randValue = rand() % 5;
                int type;
                if (randValue == 4) {
                    type = 2;
                } else if (randValue == 3) {
                    type = 1;
                } else
                    type = 0;
                _powersUp.emplace_back(
                    indie::object3D::PowerUp(pos, sceneManager, videoDriver,
                                             static_cast<macro::PowerUpType>(type),
                                             device));
            }
            for (auto &power : _powersUp) {
                power.update(device);
                power.interact(*_player, device);
            }
            unsigned int idx = 0;
            for (auto &ia : _ia) {
                if (tmpMap != map) {
                    _collisionIA.at(idx).drop(*ia);
                    _collisionIA.at(idx).create(_board.getWall(), *ia,
                                                sceneManager);
                }
                idx++;
            }
            idx = 0;
            tmpMap = map;
            for (auto &ia : _ia) {
                map = ia->update(*_player, device, sceneManager, videoDriver,
                                 map, _board.getWall(), _collisionIA.at(idx));
                _board.setMap(map);
                idx++;
            }
            idx = 0;
            if (tmpMap != map) {
                if (!_player->isInvincible()) {
                    _collision.drop(*_player);
                    _collision.create(_board.getWall(), *_player, sceneManager);
                }
                for (auto &ia : _ia) {
                    _collisionIA.at(idx).drop(*ia);
                    _collisionIA.at(idx).create(_board.getWall(), *ia,
                                                sceneManager);
                    idx++;
                }
                _board.setMap(map);
            }
            std::list<indie::object3D::Bomb> bombList = _player->getBombList();
            for (auto &bomb : bombList) {
                if (!_player->isDie() &&
                    bomb.explosionHit(_player->getPosition())) {
                    _player->setDie();
                }
                for (auto &ia : _ia) {
                    if (!ia->isDie() &&
                        bomb.explosionHit(ia->getScene()->getPosition())) {
                        ia->setDie();
                    }
                }
            }
            for (auto &iaBomb : _ia) {
                bombList = iaBomb->getBombList();
                for (auto &bomb : bombList) {
                    if (!_player->isDie() &&
                        bomb.explosionHit(_player->getPosition())) {
                        _player->setDie();
                    }
                    for (auto &ia : _ia) {
                        if (!ia->isDie() && bomb.explosionHit(
                            ia->getScene()->getPosition())) {
                            ia->setDie();
                        }
                    }
                }
            }
            for (auto &ia : _ia) {
                _player->hit(*ia);
            }
        if (_player->isDie()) {
            endGame = true;
            lost = true;
        }
        bool isAllIaDie = true;
        for (auto &ia : _ia) {
            if (!ia->isDie())
                isAllIaDie = false;
        }
        if (isAllIaDie)
            endGame = true;
        } else {
            signal = _pause->draw(videoDriver);
        }
        if (device->_eventHandler->isKeyReleased(irr::KEY_KEY_P))
            pauseMenu = !pauseMenu;
        if (device->_eventHandler->isKeyReleased(irr::KEY_RETURN) || signal == indie::macro::_SAVE_1)
            saveGame(device);
        videoDriver->endScene();
        if (signal == indie::macro::_QUIT) {
            device->closeDevice();
        }
        signal = indie::macro::ButtonSignal::_DEFAULT;
        if (endGame || device->_eventHandler->isKeyReleased(irr::KEY_BACK))
            break;
    }
    bool reRun = false;
    indie::object::Text endGameText("END GAME! You loose. Your score: " + std::to_string(_player->getScore()), irr::video::SColor(255, 255, 255, 255), irr::core::rect<irr::s32>(600, 50, 1200, 300), device->getGuiEnvironement());
    if (!lost) {
        endGameText.setText("END GAME! You won. Your score: " + std::to_string(_player->getScore()));
    }
    while (device->isRunning() && endGame) {
        videoDriver->beginScene(true, true,
                                irr::video::SColor(0, 0, 0, 0));
        signal = _endGame->draw(videoDriver);
        endGameText.draw(videoDriver);
        videoDriver->endScene();
        if (signal == indie::macro::_QUIT) {
            device->closeDevice();
        } else if (signal == indie::macro::_NEW_GAME) {
            reset(sceneManager, videoDriver, device, device->getGuiEnvironement());
            reRun = true;
            for (auto &power : _powersUp) {
                power.drop();
            }
            _powersUp.clear();
            break;
        }
    }
    if (reRun)
        run(sceneManager, videoDriver, device);
    _board.drop();
    _collision.drop(*_player);
    _player->setVisible(false);
    _player->reset();
    int idx = 0;
    for (auto &ia : _ia) {
        _collisionIA.at(idx).drop(*ia);
        ia->setVisible(false);
        ia->reset();
        idx++;
    }
}

void indie::game::Game::saveGame(indie::object::Window *device)
{
    std::ofstream saveFile(".save/.users/." + device->getUserName() + "_save/.usersave.xml");
    saveFile << "<?xml version='1.0' encoding='utf-8'?>\n";
    XMLReader xml;
    std::map<std::string, std::string> accountInfo;
    std::list<std::string> content;

    xml.startGroup("gameSave");
    std::vector<std::string> map = _board.getMap();
    std::string tmp;
    for (const auto &line : map)
        tmp.append(line);
    accountInfo["map"] = tmp;
    accountInfo["playerIndex"] = std::to_string(_playerIndex);
    accountInfo["Invincible"] = std::to_string(_player->isInvincible());
    accountInfo["BombCounter"] = std::to_string(_player->getbombNumber());
    accountInfo["Score"] = std::to_string(_player->getScore());
    int iaNumber = 0;
    for (auto &ia : _ia) {
        if (!ia->isDie())
            iaNumber++;
    }
    accountInfo["IaNumber"] = std::to_string(iaNumber);
    accountInfo["PlayerPosition"] = std::to_string(_player->getPosition().X) + ";" + std::to_string(_player->getPosition().Y) + ";" + std::to_string(_player->getPosition().Z);
    xml.writeInfo(accountInfo);
    xml.endGroup("gameSave");
    content = xml.getContent();
    content = xml.getContent();
    saveFile.close();
    encrypt::Encryption::fileFromString(content, ".save/.users/." + device->getUserName() + "_save/.usersave.xml");

}