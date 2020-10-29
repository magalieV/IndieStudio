/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Player
 *
 * File creation = 09/06/2020
 * Last modification = 09/06/2020
 */

#ifndef __BOMBERMAN_PLAYER_HPP__
#define __BOMBERMAN_PLAYER_HPP__

#include "Engine/Window.hpp"
#include "objects/Armature.hpp"
#include "MacroIndie.hpp"
#include "Bomb.hpp"
#include "StaticObject.hpp"

namespace indie::engine{
    class CollisionSystem;
}

namespace indie::object3D {
    class Player : public indie::object3D::Armature {
        public:
            Player(indie::object3D::Armature *armature);
            Player() = default;
            Player& operator=(const Player &other);
            void resetTime(irr::u32 time);
            void moovePlayer(indie::object::Window *device);
            std::vector<std::string> update(indie::object::Window *device,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                const std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                std::vector<std::string> &map,
                std::list<indie::object3D::StaticObject> &wall,
                indie::engine::CollisionSystem &collision);
            [[nodiscard]] std::list<irr::core::vector3df> getLastDeleteWall() const;
            void setEffect(indie::macro::PowerUpType powerType, indie::object::Window *device);
            void setInvincible(indie::engine::CollisionSystem &collision, indie::object::Window *device,
                std::list<indie::object3D::StaticObject> &wall,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager);
            void setNumberOfBomb(unsigned int nb);
            [[nodiscard]] unsigned int getbombNumber() const;
            [[nodiscard]] bool isInvincible() const;
            void invincible(bool state, indie::object::Window *device);
            std::vector<std::string> updateBreakable(indie::engine::CollisionSystem &collision,
                std::list<indie::object3D::StaticObject> &wall, const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                indie::object::Window *device, std::vector<std::string> &map);
            unsigned int getScore();
            void setScore(unsigned int score);
            void setDie();
            void reset();
            bool isDie() const;
            void hit(Player &other);
            [[nodiscard]] std::list<indie::object3D::Bomb> getBombList() const;
            void setKeyCodeMap(std::map<indie::macro::MovementManager, irr::EKEY_CODE> map);

        protected:
            irr::u32 _timeBefore;
            unsigned int _numberOfBomb;
            const unsigned int maxNumberBomb = 5;
            std::list<indie::object3D::Bomb> _listBomb;
            std::list<irr::core::vector3df> _lastDeleteWall;
            bool _isInvincible;
            irr::u32 _invincibleTimerStart;
            unsigned int _score;
            bool _isDie;
            bool _startUpdate;
            std::map<indie::macro::MovementManager, irr::EKEY_CODE> _movementMap;
    };
}

#endif //__BOMBERMAN_PLAYER_HPP__
