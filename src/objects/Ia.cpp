/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = IA
 *
 * File creation = 12/06/2020
 * Last modification = 12/06/2020
 */

#include "objects/Ia.hpp"

indie::object3D::IA::IA(indie::object3D::Armature *armature) : Player(armature)
{
    this->reiniRotation();
    _bombPos = false;
    _timeMove = 0;
}

indie::object3D::IA & indie::object3D::IA::operator=(const IA &other)
{
    _timeBefore = other._timeBefore;
    _timeMove = 0;
    return *this;
}

std::vector<std::string> indie::object3D::IA::update(indie::object3D::Player player,indie::object::Window *device,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    const std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
    std::vector<std::string> &map,
    std::list<indie::object3D::StaticObject> &wall,
    indie::engine::CollisionSystem &collision)
{
    if (_isDie) {
        updateBreakable(collision, wall, sceneManager, device, map);
        return map;
    }
    auto timePasse = device->getTime();
    std::vector<std::string> finder;
    indie::macro::MovementManager movement = indie::macro::MovementManager::_DEFAULT_MOVE;
    bool newMove = true;
    bool mustPosBomb = false;

    int intPartX = int(player.getPosition().X);
    int intPartZ = int(player.getPosition().Z);
    if (intPartX < 0)
        intPartX = 1;
    if (intPartZ > -1)
        intPartZ = -1;
    if (intPartX + 0.5 < player.getPosition().X)
        intPartX += 1;
    if (intPartZ - 0.5 > player.getPosition().Z)
        intPartZ -= 1;
    int intPartXI = int(getPosition().X);
    int intPartZI = int(getPosition().Z);
    if (intPartXI < 0)
        intPartXI = 1;
    if (intPartZI > -1)
        intPartZI = -1;
    if (intPartXI + 0.5 < getPosition().X)
        intPartXI += 1;
    if (intPartZI - 0.5 > getPosition().Z)
        intPartZI -= 1;
    irr::u32 timeNow = device->getTime();
    irr::f32 framerate = (irr::f32)(timeNow - _timeMove) / 1000.f;
    _timeMove = timeNow;
    if (_bombPos && float(timePasse - _timeBefore) / 1000.f < 5) {
        if (std::pair<int, int>(int(intPartXI), int(intPartZI)) == _safePos) {
            map = updateBreakable(collision, wall, sceneManager, device, map);
            standUp();
            return map;
        }
        map = updateBreakable(collision, wall, sceneManager, device, map);
        finder = _pathFinder.findPath(map, _safePos,std::pair<int, int>(int(intPartXI),int(intPartZI)));
    } else if ((_bombPos && float(timePasse - _timeBefore) / 1000.f > 5) || !_bombPos) {
        _bombPos = false;
        finder = _pathFinder.findPath(map,std::pair<int, int>(intPartX, intPartZ),std::pair<int, int>(int(intPartXI),int(intPartZI)));
    }
    if (finder.empty()) {
        standUp();
        return map;
    }
    if (_startUpdate) {
        _timeMove = device->getTime();
        timeNow = device->getTime();
        framerate = (irr::f32)(timeNow - _timeMove) / 1000.f;
        _startUpdate = false;
        _lastMovement = indie::macro::MovementManager::_DEFAULT_MOVE;
        _goal = std::pair<int, int>(intPartXI, intPartZI);
    }
    if (_lastMovement == indie::macro::MovementManager::_UPE && _goal.second > getPosition().Z)
        newMove = false;
    else if (_lastMovement == indie::macro::MovementManager::_DOWN && _goal.second < getPosition().Z)
        newMove = false;
    else if (_lastMovement == indie::macro::MovementManager::_LEFT && _goal.first < getPosition().X)
        newMove = false;
    else if (_lastMovement == indie::macro::MovementManager::_RIGHT && _goal.first > getPosition().X)
        newMove = false;

    if (newMove) {
        std::map<std::pair<int, int>, indie::macro::MovementManager> allPos =
            {{std::pair<int, int>(1 + intPartXI, 0 + (intPartZI *
                                                      -1)),              indie::macro::MovementManager::_RIGHT},
             {std::pair<int, int>(0 + intPartXI, 1 + (intPartZI *
                                                      -1)),              indie::macro::MovementManager::_DOWN},
             {std::pair<int, int>(-1 + intPartXI, 0 + (intPartZI *
                                                       -1)),             indie::macro::MovementManager::_LEFT},
             {std::pair<int, int>(0 + intPartXI, -1 + (intPartZI *
                                                       -1)),             indie::macro::MovementManager::_UPE}};
        for (const auto &direction : allPos) {
            if (direction.first.first > 0 && direction.first.second > 0 &&
                direction.first.first < BOARD_SIZE &&
                direction.first.second < BOARD_SIZE && !_bombPos
                && map.at(direction.first.second).at(direction.first.first) == 'Z') {
                mustPosBomb = true;
                break;
            }
            if (direction.first.first > 0 && direction.first.second > 0 &&
                direction.first.first < BOARD_SIZE &&
                direction.first.second < BOARD_SIZE
                &&
                finder.at(direction.first.second).at(direction.first.first) !=
                'X' &&
                map.at(direction.first.second).at(direction.first.first) !=
                'Z' && finder.at(direction.first.second).at(direction.first.first) != '*') {
                movement = direction.second;
                _goal = std::pair<int, int>(intPartXI, intPartZI);
                _lastMovement = movement;
                if (_lastMovement == indie::macro::MovementManager::_UPE)
                    _goal.second += 1;
                else if (_lastMovement == indie::macro::MovementManager::_DOWN)
                    _goal.second -= 1;
                else if (_lastMovement == indie::macro::MovementManager::_LEFT)
                    _goal.first -= 1;
                else if (_lastMovement == indie::macro::MovementManager::_RIGHT)
                    _goal.first += 1;
                break;
            }
        }
    } else {
        movement = _lastMovement;
    }
    if (mustPosBomb) {
        _timeBefore = device->getTime();
        _bombPos = true;
        _safePos = _pathFinder.findSafePlace(map, std::pair<int, int>(int(intPartXI), int(intPartZI)));
        _safePos.second *= -1;
        _listBomb.emplace_back(indie::object3D::Bomb(2, device, 80, sceneManager, videoDriver));
        _listBomb.back().setPosition({float(intPartXI), 0.f, float(intPartZI)}, map);
    }
    irr::core::vector3df actualRotation = getRotation();
    irr::core::vector3df actualPosition = getPosition();
    if (movement == indie::macro::MovementManager::_UPE) {
        actualPosition.Z += (PLAYER_SPEED - 1.5) * framerate;
        run();
        if (actualRotation != irr::core::vector3df(0, 180, 0)) {
            if (actualRotation.Y <= 160)
                setRotation({0, actualRotation.Y + 20, 0});
            else if (actualRotation.Y >= 200)
                setRotation({0, actualRotation.Y - 20, 0});
            else
                setRotation({0, 180, 0});
        }
    } else if (movement == indie::macro::MovementManager::_DOWN) {
        actualPosition.Z -= (PLAYER_SPEED - 1.5) * framerate;
        run();
        if (actualRotation != irr::core::vector3df(0, 0, 0)) {
            if (actualRotation.Y >= 20 && actualRotation.Y <= 180)
                setRotation({0, actualRotation.Y - 20, 0});
            else if (actualRotation.Y > 180 && actualRotation.Y <= 340)
                setRotation({0, actualRotation.Y + 20, 0});
            else
                setRotation({0, 0, 0});
        }
    } else if (movement == indie::macro::MovementManager::_LEFT) {
        actualPosition.X -= (PLAYER_SPEED - 1.5) * framerate;
        run();
        if (actualRotation !=irr::core:: vector3df(0, 90, 0)) {
            if (actualRotation.Y <= 70 || actualRotation.Y >= 270)
                setRotation({0, static_cast<float>(static_cast<int>(actualRotation.Y + 20) % 360), 0});
            else if (actualRotation.Y >= 110 && actualRotation.Y < 270)
                setRotation({0, actualRotation.Y - 20, 0});
            else
                setRotation({0, 90, 0});
        }
    } else if (movement == indie::macro::MovementManager::_RIGHT) {
        actualPosition.X += (PLAYER_SPEED - 1.5) * framerate;
        run();
        if (actualRotation != irr::core::vector3df(0, 270, 0)) {
            if (actualRotation.Y <= 250 && actualRotation.Y >= 90)
                setRotation({0, actualRotation.Y + 20, 0});
            else if (actualRotation.Y >= 290 || actualRotation.Y < 90) {
                if (actualRotation.Y <= 0)
                    setRotation({0, 360, 0});
                actualRotation = getRotation();
                setRotation({0, actualRotation.Y - 20, 0});
            } else
                setRotation({0, 270, 0});
        }
    } else {
        standUp();
    }
    actualPosition.Y = 0;
    setPosition(actualPosition);
    return map;
}