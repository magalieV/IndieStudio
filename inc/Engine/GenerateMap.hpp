/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = GenerateMap
 *
 * File creation = 07/06/2020
 * Last modification = 07/06/2020
 */

#ifndef __BOMBERMAN_GENERATEMAP_HPP__
#define __BOMBERMAN_GENERATEMAP_HPP__

#include <iostream>
#include <vector>

namespace indie::engine {
    class GenerateMap {
        public:
            GenerateMap() = default;
            std::vector<std::string> generate();

        private:
            std::vector<std::string> createMap(std::pair<int, int> size);
            std::vector<std::string> createPath(std::vector<std::string> map);
            std::pair<int, int> choosePosPath(std::vector<std::string> labyrinth, std::pair<int, int> pos);
            bool checkAround(std::vector<std::string> map, std::pair<int, int> pos, std::pair<int, int> lastPos);
            std::vector<std::string> concatLabyrinth(std::vector<std::string> first);
            unsigned int countAround(std::vector<std::string> map, std::pair<int, int> pos);
            std::vector<std::string> putHorizontalWall(std::vector<std::string> map);
    };
}

#endif //__BOMBERMAN_GENERATEMAP_HPP__
