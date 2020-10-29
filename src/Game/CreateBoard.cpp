/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = CreateBoard
 *
 * File creation = 08/06/2020
 * Last modification = 08/06/2020
 */

#include "Game/CreateBoard.hpp"
#include "MacroIndie.hpp"

indie::game::CreateBoard::CreateBoard(
    std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager)
{
    createGround(videoDriver, sceneManager);
    _map = _generator.generate();
    createObject(videoDriver, sceneManager);
}

indie::game::CreateBoard::CreateBoard(
    std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    const std::vector<std::string> &map)
{
    createGround(videoDriver, sceneManager);
    _map = map;
    createObject(videoDriver, sceneManager);
}

void indie::game::CreateBoard::createGround(std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager)
{
    for (unsigned int index = 0; index < BOARD_SIZE; index++) {
        for (unsigned int idx = 0; idx < BOARD_SIZE; idx++) {
            _board.emplace_back(indie::object3D::StaticObject("assets/game/wall/Ground.3ds", "assets/game/wall/Ground.TGA", {float(idx), 0, -(float(index))}, sceneManager, videoDriver));
        }
    }
}

void indie::game::CreateBoard::createObject(
    std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager)
{
    for (unsigned int index = 0; index < _map.size(); index++) {
        for (unsigned int idx = 0; idx < _map.at(index).size(); idx++) {
            if (_map.at(index).at(idx) == 'X') {
                _wall.emplace_back(indie::object3D::StaticObject("assets/game/wall/Unbreakable.3ds", "assets/game/wall/Unbreakable.TGA", {float(idx), 0, -(float(index))}, sceneManager, videoDriver));
                _board.emplace_back(_wall.back());
            } else if (_map.at(index).at(idx) == 'Z') {
                _wall.emplace_back(indie::object3D::StaticObject("assets/game/wall/Breakable.3ds", "assets/game/wall/Breakable.TGA", {float(idx), 0, -(float(index))}, sceneManager, videoDriver));
                _board.emplace_back(_wall.back());
            }
        }
    }
}

std::list<indie::object3D::StaticObject> &indie::game::CreateBoard::getWall()
{
    return _wall;
}

std::vector<std::string> indie::game::CreateBoard::getMap() const
{
    return _map;
}

void indie::game::CreateBoard::setMap(std::vector<std::string> map)
{
    _map = map;
}

void indie::game::CreateBoard::drop()
{
    for (auto &wall : _board) {
        wall.setVisible(false);
        wall.getScene()->removeAnimators();
        wall.getScene()->remove();
    }
    _wall.clear();
    _board.clear();
}