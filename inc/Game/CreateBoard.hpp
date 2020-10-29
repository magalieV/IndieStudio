/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = CreateBoard
 *
 * File creation = 08/06/2020
 * Last modification = 08/06/2020
 */

#ifndef __BOMBERMAN_CREATEBOARD_HPP__
#define __BOMBERMAN_CREATEBOARD_HPP__

#include <Engine/Window.hpp>
#include "objects/StaticObject.hpp"
#include "Engine/GenerateMap.hpp"

namespace indie::game {
    class CreateBoard {
        public:
            CreateBoard() = default;
            CreateBoard(std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
                const std::vector<std::string> &map);
            CreateBoard(std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager);
            [[nodiscard]] std::list<indie::object3D::StaticObject> &getWall();
            [[nodiscard]] std::vector<std::string> getMap() const;
            void setMap(std::vector<std::string> map);
            void drop();
        private:
            void createGround(std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                const std::shared_ptr<irr::scene::ISceneManager> &sceneManager);
            void createObject(std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
                              const std::shared_ptr<irr::scene::ISceneManager> &sceneManager);
        private:
            std::list<indie::object3D::StaticObject> _board;
            std::list<indie::object3D::StaticObject> _wall;
            indie::engine::GenerateMap _generator;
            std::vector<std::string> _map;
    };
}

#endif //__BOMBERMAN_CREATEBOARD_HPP__
