/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Game
 *
 * File creation = 10/06/2020
 * Last modification = 10/06/2020
 */

#ifndef __BOMBERMAN_GAME_HPP__
#define __BOMBERMAN_GAME_HPP__

#include <Engine/CollisionSystem.hpp>
#include "objects/Player.hpp"
#include "objects/Armature.hpp"
#include "Game/CreateBoard.hpp"
#include "banks/PictureBank.hpp"
#include "banks/ObjectBank.hpp"
#include "Game//Pause.hpp"
#include "objects/Ia.hpp"
#include "Game/EndGame.hpp"

namespace indie::game {
    class Game {
        public:
            Game() = default;
            void run(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                std::shared_ptr<irr::video::IVideoDriver> &videoDriver, indie::object::Window *device);
            void saveGame(indie::object::Window *device);
            Game(std::vector<indie::object3D::Armature *> _allNpc, unsigned int actualNpc,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                std::shared_ptr<irr::video::IVideoDriver> videoDriver,
                indie::game::CreateBoard &board, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);
            void loadGame(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                std::shared_ptr<irr::video::IVideoDriver> videoDriver, indie::object::Window *device,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);
            void reset(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                       std::shared_ptr<irr::video::IVideoDriver> videoDriver, indie::object::Window *device,
                       const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);
        private:
            unsigned int _playerIndex;
            indie::object3D::Player *_player;
            indie::bank::PictureBank _pictureBank;
            indie::bank::ObjectBank _objectBank;
            irr::scene::ICameraSceneNode* _camera;
            indie::object::Picture _background;
            indie::game::CreateBoard _board;
            indie::engine::CollisionSystem _collision;
            indie::game::Pause *_pause;
            std::list<indie::object3D::IA *> _ia;
            std::vector<indie::object3D::Armature *> _playerChoice;
            std::vector<indie::engine::CollisionSystem> _collisionIA;
            indie::game::EndGame *_endGame;
    };
}

#endif //__BOMBERMAN_GAME_HPP__
