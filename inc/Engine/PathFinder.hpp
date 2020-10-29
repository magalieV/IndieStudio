/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = PathFinder
 *
 * File creation = 12/06/2020
 * Last modification = 12/06/2020
 */

#ifndef __BOMBERMAN_PATHFINDER_HPP__
#define __BOMBERMAN_PATHFINDER_HPP__

#include <iostream>
#include <vector>

namespace indie::engine {
    class PathFinder {
        public:
            PathFinder() = default;
            std::vector<std::string> findPath(std::vector<std::string> map, std::pair<int, int> tracker,
                std::pair<int, int> actualPos);
            std::pair<int, int> findSafePlace(std::vector<std::string> map, std::pair<int, int> actualPos);
        private:
            std::pair<std::pair<int, int>, bool> findWaySafe(std::vector<std::vector<int>> maze, std::vector<std::string> map, int depth, std::pair<int, int> pos);
            std::vector<std::vector<int>> findWay(std::vector<std::vector<int>> maze, std::vector<std::string> map, int depth, std::pair<int, int> pos, std::pair<int, int> target);
            std::vector<std::vector<int>> initDepthMap();
            std::vector<std::string> drawCircle(std::pair<int, int> pos, std::vector<std::vector<int>> maze, std::vector<std::string> map);
    };
}

#endif //__BOMBERMAN_PATHFINDER_HPP__
