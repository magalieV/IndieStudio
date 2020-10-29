/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = MultiplayerGame
 *
 * File creation = 13/06/2020
 * Last modification = 13/06/2020
 */

#ifndef __BOMBERMAN_MULTIPLAYERGAME_HPP__
#define __BOMBERMAN_MULTIPLAYERGAME_HPP__

#include <Engine/CollisionSystem.hpp>
#include <objects/Text.hpp>
#include "objects/Player.hpp"
#include "objects/Armature.hpp"
#include "Game/CreateBoard.hpp"
#include "banks/PictureBank.hpp"
#include "banks/ObjectBank.hpp"
#include "Game//Pause.hpp"
#include "objects/Ia.hpp"
#include "Game/EndGame.hpp"

namespace indie::game {
    class MultiplayerGame {
        public:
            MultiplayerGame(unsigned int numberPlayer,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                std::shared_ptr<irr::video::IVideoDriver> videoDriver,
                indie::game::CreateBoard &board,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement, indie::object::Window *device);
            void reset(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                std::shared_ptr<irr::video::IVideoDriver> videoDriver,
                indie::object::Window *device,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement);
            void run(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                indie::object::Window *device);

        private:
            unsigned int _playerIndex;
            std::vector<indie::object3D::Player *> _players;
            indie::bank::PictureBank _pictureBank;
            indie::bank::ObjectBank _objectBank;
            irr::scene::ICameraSceneNode *_camera;
            indie::object::Picture _background;
            indie::game::CreateBoard _board;
            indie::game::Pause *_pause;
            std::vector<indie::object3D::Armature *> _playerChoice;
            std::vector<indie::engine::CollisionSystem> _collision;
            indie::game::EndGame *_endGame;
            std::vector<indie::object::Text> _scoreText;
            std::vector<indie::object::Text> _bombText;

    };
}

#endif //__BOMBERMAN_MULTIPLAYERGAME_HPP__
