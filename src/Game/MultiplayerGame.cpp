/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = MultiplayerGame
 *
 * File creation = 13/06/2020
 * Last modification = 13/06/2020
 */

#include "Game/MultiplayerGame.hpp"
#include "objects/PowerUp.hpp"
#include "objects/Text.hpp"
#include <string>

indie::game::MultiplayerGame::MultiplayerGame(unsigned int numberPlayer,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    std::shared_ptr<irr::video::IVideoDriver> videoDriver,
    indie::game::CreateBoard &board,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement, indie::object::Window *device) : _board(board)
{
    std::vector<std::map<indie::macro::MovementManager, irr::EKEY_CODE> > mapKeyCode;
    mapKeyCode.emplace_back(std::map<indie::macro::MovementManager, irr::EKEY_CODE>{{indie::macro::_LEFT, irr::KEY_LEFT}, {indie::macro::_DOWN, irr::KEY_DOWN}, {indie::macro::_UPE, irr::KEY_UP}, {indie::macro::_RIGHT, irr::KEY_RIGHT}, {indie::macro::_BOMB, irr::KEY_RETURN}});
    mapKeyCode.emplace_back(std::map<indie::macro::MovementManager, irr::EKEY_CODE>{{indie::macro::_LEFT, irr::KEY_KEY_Q}, {indie::macro::_DOWN, irr::KEY_KEY_S}, {indie::macro::_UPE, irr::KEY_KEY_Z}, {indie::macro::_RIGHT, irr::KEY_KEY_D}, {indie::macro::_BOMB, irr::KEY_KEY_A}});
    mapKeyCode.emplace_back(std::map<indie::macro::MovementManager, irr::EKEY_CODE>{{indie::macro::_LEFT, irr::KEY_KEY_J}, {indie::macro::_DOWN, irr::KEY_KEY_K}, {indie::macro::_UPE, irr::KEY_KEY_I}, {indie::macro::_RIGHT, irr::KEY_KEY_L}, {indie::macro::_BOMB, irr::KEY_KEY_M}});
    mapKeyCode.emplace_back(std::map<indie::macro::MovementManager, irr::EKEY_CODE>{{indie::macro::_LEFT, irr::KEY_KEY_V}, {indie::macro::_DOWN, irr::KEY_KEY_B}, {indie::macro::_UPE, irr::KEY_KEY_G}, {indie::macro::_RIGHT, irr::KEY_KEY_N}, {indie::macro::_BOMB, irr::KEY_SPACE}});

    _playerIndex = numberPlayer;
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerOne.b3d", "assets/game/player/PlayerColorSetOne.png", {0, 0, 0}, sceneManager, videoDriver));
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerTwo.b3d", "assets/game/player/PlayerColorSetTwo.png", {0, 0, 0}, sceneManager, videoDriver));
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerThree.b3d", "assets/game/player/PlayerColorSetThree.png", {0, 0, 0}, sceneManager, videoDriver));
    _playerChoice.emplace_back(new indie::object3D::Armature("assets/game/player/PlayerFour.b3d", "assets/game/player/PlayerColorSetYellow.png", {0, 0, 0}, sceneManager, videoDriver));
    _background = indie::object::Picture("assets/game/game_back.png",
                                         std::pair<float, float>(0, 0),
                                         std::pair<float, float>(1920, 1080),
                                         videoDriver);
    _pause = new indie::game::Pause(sceneManager, videoDriver, guiEnvironnement, false);
    _endGame = new indie::game::EndGame(sceneManager, videoDriver, guiEnvironnement);
    std::vector<irr::core::rect<int>> posPicture;
    posPicture.emplace_back(irr::core::rect<int>(0, 100, 330, 200));
    posPicture.emplace_back(irr::core::rect<int>(0, 500, 330, 200));
    posPicture.emplace_back(irr::core::rect<int>(1300, 100, 330, 200));
    posPicture.emplace_back(irr::core::rect<int>(1300, 500, 330, 200));
    unsigned int index = 0;
    for (auto &player : _playerChoice) {
        index++;
        if (index > numberPlayer) {
            player->setVisible(false);
        } else {
            _players.emplace_back(new indie::object3D::Player(player));
            _pictureBank.add(indie::object::Picture(
                "assets/game/game_object/player" + std::to_string(index) +
                ".png", std::pair<float, float>(posPicture.at(index - 1).UpperLeftCorner.X, (posPicture.at(index - 1).UpperLeftCorner.Y)),
                std::pair<float, float>(posPicture.at(index - 1).LowerRightCorner.X, (posPicture.at(index - 1).LowerRightCorner.Y)), videoDriver));
            _pictureBank.add(indie::object::Picture("assets/game/game_object/bomb.png",
                std::pair<float, float>(posPicture.at(index - 1).UpperLeftCorner.X, (posPicture.at(index - 1).UpperLeftCorner.Y) + 200),
                std::pair<float, float>(50, 48),
                videoDriver));
            _bombText.emplace_back(indie::object::Text("5", irr::video::SColor(255, 255, 255, 255), irr::core::rect<irr::s32>(posPicture.at(index - 1).UpperLeftCorner.X + 50, (posPicture.at(index - 1).UpperLeftCorner.Y) + 200, 80, 300), guiEnvironnement));
            _scoreText.emplace_back(indie::object::Text("Score: 0", irr::video::SColor(255, 255, 255, 255), irr::core::rect<irr::s32>(posPicture.at(index - 1).UpperLeftCorner.X + 100, (posPicture.at(index - 1).UpperLeftCorner.Y) + 200, 80, 300), guiEnvironnement));
            _players.back()->reiniRotation();
            _players.back()->resetTime(device->getTime());
            _players.back()->setKeyCodeMap(mapKeyCode.at(index - 1));
        }
    }
    _objectBank.addObject(&_pictureBank);
    _camera = sceneManager->addCameraSceneNode(nullptr, irr::core::vector3df(
        BOARD_SIZE / 2, 13, -BOARD_SIZE / 3 * 2), irr::core::vector3df(0, 100,
                                                                       200));
    _camera->setTarget(
        irr::core::vector3df(BOARD_SIZE / 2, 0, -BOARD_SIZE / 2));
    std::vector<float> npcPos = {1.f, 1.f, 1.f, BOARD_SIZE - 2, BOARD_SIZE - 2, 1.f,
                                 BOARD_SIZE - 2, BOARD_SIZE - 2};
    unsigned int counter = 0;
    for (auto player : _players) {
        player->setPosition(
            {npcPos.at(counter), 0.f, npcPos.at(counter + 1) * -1.f});
        counter += 2;
    }
    for (auto player : _players) {
        _collision.emplace_back(indie::engine::CollisionSystem());
        _collision.back().create(_board.getWall(), *player, sceneManager);
    }
}

void indie::game::MultiplayerGame::reset(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager, std::shared_ptr<irr::video::IVideoDriver> videoDriver, indie::object::Window *device, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    std::vector<float> npcPos = {1.f, 1.f, 1.f, BOARD_SIZE - 2, BOARD_SIZE - 2, 1.f,
                                 BOARD_SIZE - 2, BOARD_SIZE - 2};
    unsigned int counter = 0;
    for (auto &player : _players) {
        player->setNumberOfBomb(5);
        player->setScore(0);
        player->invincible(false, device);
        player->setPosition({npcPos.at(counter), 0, npcPos.at(counter + 1) * -1.f});
        player->reiniRotation();
        player->reset();
        counter += 2;
    }
    int idx = 0;
    indie::engine::GenerateMap generator;
    _board.drop();
    _board = indie::game::CreateBoard(videoDriver, sceneManager, generator.generate());
    for (auto player : _players) {
        _collision.at(idx).drop(*player);
        _collision.at(idx).create(_board.getWall(), *player, sceneManager);
        idx++;
    }
}

void indie::game::MultiplayerGame::run(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager, std::shared_ptr<irr::video::IVideoDriver> &videoDriver, indie::object::Window *device)
{
    std::vector<std::string> map = _board.getMap();
    int randValue;
    std::list<indie::object3D::PowerUp> _powersUp;
    std::string tmp;
    bool pauseMenu = false;
    indie::macro::ButtonSignal signal = indie::macro::ButtonSignal::_DEFAULT;
    std::vector<std::string> tmpMap = map;
    bool endGame = false;
    bool changeMap = false;
    int idx = 0;

    while (device->isRunning()) {
        videoDriver->beginScene(true, true,
                                irr::video::SColor(0, 255, 255, 255));
        _background.draw(videoDriver);
        sceneManager->drawAll();
        _objectBank.draw(videoDriver);
        if (!pauseMenu) {
            changeMap = false;
            int index = 0;
            for (auto &score : _scoreText) {
                score.setText("Score: " + std::to_string(_players.at(index)->getScore()));
                _bombText.at(index).setText(std::to_string(_players.at(index)->getbombNumber()));
                _bombText.at(index).draw(videoDriver);
                score.draw(videoDriver);
                index++;
            }
            index = 0;
            for (auto &player : _players) {
                player->moovePlayer(device);
                tmpMap = map;
                map = player->update(device, sceneManager, videoDriver, map,_board.getWall(), _collision.at(index));
                _board.setMap(map);
                if (tmpMap != map)
                    changeMap = true;
                std::list<irr::core::vector3df> walls = player->getLastDeleteWall();
                for (const auto &pos : walls) {
                    randValue = rand() % 5;
                    int type;
                    if (randValue == 4) {
                        type = 2;
                    } else if (randValue == 3) {
                        type = 1;
                    } else
                        type = 0;
                    _powersUp.emplace_back(indie::object3D::PowerUp(pos, sceneManager, videoDriver, static_cast<macro::PowerUpType>(type), device));
                }
            }
            for (auto &power : _powersUp) {
                power.update(device);
                for (auto &player : _players) {
                    power.interact(*player, device);
                }
            }
            idx = 0;
            if (changeMap) {
                for (auto &player : _players) {
                    if (!player->isInvincible()) {
                        _collision.at(idx).drop(*player);
                        _collision.at(idx).create(_board.getWall(), *player, sceneManager);
                        idx++;
                    }
                }
             }
            for (auto &player : _players) {
                for (auto &myPlayer : _players) {
                    if (player != myPlayer) {
                        player->hit(*myPlayer);
                    }
                }
                std::list<indie::object3D::Bomb> bombList = player->getBombList();
                for (auto &myPlayer : _players) {
                    for (auto &bomb : bombList) {
                        if (!myPlayer->isDie() &&
                            bomb.explosionHit(myPlayer->getPosition())) {
                            myPlayer->setDie();
                        }
                    }
                }
            }
            int isAllIaDie = 0;
            for (auto &player : _players) {
                if (player->isDie())
                    isAllIaDie += 1;
            }
            if (isAllIaDie == _playerIndex - 1) {
                endGame = true;
            }
        } else {
            signal = _pause->draw(videoDriver);
        }
        if (device->_eventHandler->isKeyReleased(irr::KEY_KEY_P))
            pauseMenu = !pauseMenu;
        videoDriver->endScene();
        if (signal == indie::macro::_QUIT) {
            device->closeDevice();
        }
        signal = indie::macro::ButtonSignal::_DEFAULT;
        if (endGame || device->_eventHandler->isKeyReleased(irr::KEY_BACK))
            break;
    }
    bool reRun = false;
    indie::object::Text textScore;
    int i = 0;
    for (auto &player : _players) {
        if (!player->isDie()) {
            textScore = indie::object::Text("END GAME! Player " + std::to_string(i + 1) + "won. Your score: " + std::to_string(player->getScore()), irr::video::SColor(255, 255, 255, 255), irr::core::rect<irr::s32>(600, 50, 1200, 300), device->getGuiEnvironement());
            break;
        }
        i++;
    }
    while (device->isRunning() && endGame) {
        videoDriver->beginScene(true, true,
                                irr::video::SColor(0, 0, 0, 0));
        _objectBank.draw(videoDriver);
        signal = _endGame->draw(videoDriver);
        textScore.draw(videoDriver);
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
    idx = 0;
    for (auto player : _players) {
        _collision.at(idx).drop(*player);
        player->setVisible(false);
        player->reset();
        idx++;
    }
}