/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Player
 *
 * File creation = 09/06/2020
 * Last modification = 09/06/2020
 */

#include "objects/Player.hpp"
#include "MacroIndie.hpp"
#include "Engine/CollisionSystem.hpp"

indie::object3D::Player::Player(indie::object3D::Armature *armature) : indie::object3D::Armature(*armature)
{
    this->reiniRotation();
    _numberOfBomb = 5;
    _isInvincible = false;
    _score = 0;
    _isDie = false;
    _startUpdate = true;
    _movementMap[indie::macro::MovementManager::_LEFT] = irr::KEY_LEFT;
    _movementMap[indie::macro::MovementManager::_RIGHT] = irr::KEY_RIGHT;
    _movementMap[indie::macro::MovementManager::_DOWN] = irr::KEY_DOWN;
    _movementMap[indie::macro::MovementManager::_UPE] = irr::KEY_UP;
    _movementMap[indie::macro::MovementManager::_BOMB] = irr::KEY_SPACE;
}

indie::object3D::Player & indie::object3D::Player::operator=(const Player &other)
{
    _timeBefore = other._timeBefore;
    _numberOfBomb = other._numberOfBomb;
    _listBomb = other._listBomb;
    _lastDeleteWall = other._lastDeleteWall;
    _isInvincible = other.isInvincible();
    _invincibleTimerStart = other._invincibleTimerStart;
    _score = other._score;
    _isDie = other._isDie;
    _startUpdate = true;
    _movementMap = other._movementMap;
    return *this;
}

void indie::object3D::Player::reset()
{
    this->reiniRotation();
    setVisible(true);
    _numberOfBomb = 5;
    _isInvincible = false;
    _score = 0;
    _isDie = false;
    for (auto &bomb : _listBomb) {
        bomb.drop();
    }
    _listBomb.clear();
    _lastDeleteWall.clear();
    _startUpdate = true;
}

void indie::object3D::Player::setKeyCodeMap(std::map<indie::macro::MovementManager, irr::EKEY_CODE> map)
{
    _movementMap = map;
}

void indie::object3D::Player::setNumberOfBomb(unsigned int nb)
{
    _numberOfBomb = nb;
}

void indie::object3D::Player::moovePlayer(indie::object::Window *device)
{
    if (_isDie)
        return;
    irr::core::vector3df actualRotation = getRotation();
    irr::core::vector3df actualPosition = getPosition();
    const irr::u32 timeNow = device->getTime();
    const irr::f32 framerate = (irr::f32)(timeNow - _timeBefore) / 1000.f;

    _timeBefore = timeNow;
    if (device->_eventHandler->isKeyPressed(_movementMap.at(indie::macro::MovementManager::_UPE))) {
        actualPosition.Z += PLAYER_SPEED * framerate;
        run();
        if (actualRotation != irr::core::vector3df(0, 180, 0)) {
            if (actualRotation.Y <= 160)
                setRotation({0, actualRotation.Y + 20, 0});
            else if (actualRotation.Y >= 200)
                setRotation({0, actualRotation.Y - 20, 0});
            else
                setRotation({0, 180, 0});
        }
    } else if (device->_eventHandler->isKeyPressed(_movementMap.at(indie::macro::MovementManager::_DOWN))) {
        actualPosition.Z -= PLAYER_SPEED * framerate;
        run();
        if (actualRotation != irr::core::vector3df(0, 0, 0)) {
            if (actualRotation.Y >= 20 && actualRotation.Y <= 180)
                setRotation({0, actualRotation.Y - 20, 0});
            else if (actualRotation.Y > 180 && actualRotation.Y <= 340)
                setRotation({0, actualRotation.Y + 20, 0});
            else
                setRotation({0, 0, 0});
        }
    } else if (device->_eventHandler->isKeyPressed(_movementMap.at(indie::macro::MovementManager::_LEFT))) {
        actualPosition.X -= PLAYER_SPEED * framerate;
        run();
        if (actualRotation !=irr::core:: vector3df(0, 90, 0)) {
            if (actualRotation.Y <= 70 || actualRotation.Y >= 270)
                setRotation({0, static_cast<float>(static_cast<int>(actualRotation.Y + 20) % 360), 0});
            else if (actualRotation.Y >= 110 && actualRotation.Y < 270)
                setRotation({0, actualRotation.Y - 20, 0});
            else
                setRotation({0, 90, 0});
        }
    } else if (device->_eventHandler->isKeyPressed(_movementMap.at(indie::macro::MovementManager::_RIGHT))) {
        actualPosition.X += PLAYER_SPEED * framerate;
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
}

void indie::object3D::Player::resetTime(irr::u32 time)
{
    _timeBefore = time;
}

std::vector<std::string> indie::object3D::Player::updateBreakable(indie::engine::CollisionSystem &collision, std::list<indie::object3D::StaticObject> &wall, const std::shared_ptr<irr::scene::ISceneManager> &sceneManager, indie::object::Window *device, std::vector<std::string> &map)
{
    std::list<irr::core::vector3df> toHide;
    for (auto &bomb : _listBomb) {
        bomb.update(device, map);
        if (bomb.isEnd()) {
            std::vector<irr::core::vector3df> bombPos = bomb.bombPosition();
            for (auto &pos : bombPos) {
                if (map.at(pos.Z * -1).at(pos.X) == 'Z') {
                    toHide.emplace_back(irr::core::vector3df(pos.X, 0, pos.Z));
                    map.at(pos.Z * -1).at(pos.X) = '*';
                }
            }
        }
    }
    std::list<int> indexList;
    unsigned int counter = 0;
    for (auto &wallToHide : wall) {
        for (const auto &position : toHide) {
            if (wallToHide.getPosition() == position) {
                _lastDeleteWall.emplace_back(position);
                wallToHide.setVisible(false);
                wallToHide.getScene()->removeAll();
                _score += 10;
                indexList.emplace_back(counter);
                collision.drop(*this);
            }
        }
        counter++;
    }
    bool change = false;
    unsigned int removeFromeIndex = 0;
    for (const auto &idx : indexList) {
        auto it = wall.begin();
        std::advance(it, (idx - removeFromeIndex));
        wall.erase(it);
        change = true;
        removeFromeIndex++;
    }
    if (change && !_isInvincible) {
        collision.create(wall, *this, sceneManager);
    }
    return map;
}

std::vector<std::string> indie::object3D::Player::update(indie::object::Window *device,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    const std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
    std::vector<std::string> &map,
    std::list<indie::object3D::StaticObject> &wall,
    indie::engine::CollisionSystem &collision)
{
    if (_isDie) {
        _lastDeleteWall.clear();
        updateBreakable(collision, wall, sceneManager, device, map);
        return map;
    }
    _lastDeleteWall.clear();
    setInvincible(collision, device, wall, sceneManager);
    if (device->_eventHandler->isKeyReleased(_movementMap.at(indie::macro::MovementManager::_BOMB)) && _numberOfBomb > 0) {
        _numberOfBomb--;
        _listBomb.emplace_back(indie::object3D::Bomb(2, device, 80, sceneManager, videoDriver));
        irr::core::vector3df playerPos = getPosition();
        int intPartX = int(playerPos.X);
        int intPartZ = int(playerPos.Z);
        if (intPartX < 0)
            intPartX = 1;
        if (intPartZ > -1)
            intPartZ = -1;
        if (intPartX + 0.5 < getPosition().X)
            intPartX += 1;
        if (intPartZ - 0.5 > getPosition().Z)
            intPartZ -= 1;
        _listBomb.back().setPosition({float(intPartX), 0.f, float(intPartZ)}, map);
    }
    return updateBreakable(collision, wall, sceneManager, device, map);
}

std::list<irr::core::vector3df> indie::object3D::Player::getLastDeleteWall() const
{
    return _lastDeleteWall;
}

void indie::object3D::Player::setEffect(indie::macro::PowerUpType powerType,
    indie::object::Window *device)
{
    if (_isDie)
        return;
    switch (powerType) {
        case indie::macro::PowerUpType::_BOMB_DOWN:
            _numberOfBomb = (int(_numberOfBomb) - 1 < 0) ? 0 : _numberOfBomb - 1;
            break;
        case indie::macro::PowerUpType::_BOMB_UP:
            _numberOfBomb = (_numberOfBomb + 1 > maxNumberBomb) ? maxNumberBomb : _numberOfBomb + 1;
            break;
        default:
            _isInvincible = true;
            _invincibleTimerStart = device->getTime();
            break;
    }
}

void indie::object3D::Player::setInvincible(indie::engine::CollisionSystem &collision,
    indie::object::Window *device,
    std::list<indie::object3D::StaticObject> &wall,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager)
{
    static bool isActually = false;

    if (isActually)
        return;
    else if (!isActually && _isInvincible) {
        collision.drop(*this);
        isActually = true;
        collision.createBorder(wall, *this, sceneManager);
    }
}

unsigned int indie::object3D::Player::getbombNumber() const
{
    return _numberOfBomb;
}

bool indie::object3D::Player::isInvincible() const
{
    return _isInvincible;
}

void indie::object3D::Player::invincible(bool state, indie::object::Window *device)
{
    _isInvincible = state;
    if (state)
        _invincibleTimerStart = device->getTime();
}

unsigned int indie::object3D::Player::getScore()
{
    return _score;
}

void indie::object3D::Player::setScore(unsigned int score)
{
    _score = score;
}

std::list<indie::object3D::Bomb> indie::object3D::Player::getBombList() const
{
    return _listBomb;
}

bool indie::object3D::Player::isDie() const
{
    return _isDie;
}

void indie::object3D::Player::setDie()
{
    getScene()->setVisible(false);
    _isDie = true;
}

void indie::object3D::Player::hit(Player &other)
{
    if (_isDie || other.isDie())
        return;
    int intPartX = int(other.getPosition().X);
    int intPartZ = int(other.getPosition().Z);
    if (intPartX < 0)
        intPartX = 1;
    if (intPartZ > -1)
        intPartZ = -1;
    if (intPartX + 0.5 < other.getPosition().X)
        intPartX += 1;
    if (intPartZ - 0.5 > other.getPosition().Z)
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
    if (intPartX == intPartXI && intPartZ == intPartZI) {
        setDie();
    }
}