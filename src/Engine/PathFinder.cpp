/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = PathFinder
 *
 * File creation = 12/06/2020
 * Last modification = 12/06/2020
 */

#include "Engine/PathFinder.hpp"
#include "MacroIndie.hpp"

std::vector<std::string> indie::engine::PathFinder::findPath(std::vector<std::string> map, std::pair<int, int> tracker, std::pair<int, int> actualPos)
{
    std::vector<std::vector<int>> result;
    std::vector<std::string> finder;

    if (tracker.first == actualPos.first && tracker.second == actualPos.second)
        return finder;
    tracker.second *= -1;
    actualPos.second *= -1;
    result = initDepthMap();
    result = findWay(result, map, 0, actualPos, tracker);
    finder = drawCircle(tracker, result, map);
    return finder;
}

std::pair<int, int> indie::engine::PathFinder::findSafePlace(std::vector<std::string> map, std::pair<int, int> actualPos)
{
    std::vector<std::vector<int>> result;
    std::vector<std::string> finder;
    std::pair<std::pair<int, int>, bool> tmp;

    actualPos.second *= -1;
    result = initDepthMap();
    tmp = findWaySafe(result, map, 0, actualPos);
    return tmp.first;
}

std::pair<std::pair<int, int>, bool> indie::engine::PathFinder::findWaySafe(
    std::vector<std::vector<int>> maze, std::vector<std::string> map, int depth,
    std::pair<int, int> pos)
{
    std::vector<int> allPos = {1, 0, 0, 1, -1, 0, 0, -1};
    int x = 0;
    int y = 0;
    std::pair<std::pair<int, int>, bool> tmp(pos, false);

    if (depth == 4)
        return std::pair<std::pair<int, int>, bool>(pos, true);
    maze.at(pos.second).at(pos.first) = depth;
    for (unsigned int index = 0; index < allPos.size(); index += 2) {
        x = pos.first + allPos.at(index);
        y = pos.second + allPos.at(index + 1);
        if (x > 0 && y > 0 && x < BOARD_SIZE && y < BOARD_SIZE
            && map.at(y).at(x) == '*' && (depth < maze.at(y).at(x) || maze.at(y).at(x) == -1)) {
            tmp = findWaySafe(maze, map, depth + 1, std::pair<int, int>(x, y));
            if (tmp.second)
                return tmp;
        }
    }
    return tmp;
}

std::vector<std::vector<int>> indie::engine::PathFinder::findWay(
    std::vector<std::vector<int>> maze, std::vector<std::string> map, int depth,
    std::pair<int, int> pos, std::pair<int, int> target)
{
    std::vector<int> allPos = {1, 0, 0, 1, -1, 0, 0, -1};
    int x = 0;
    int y = 0;

    maze.at(pos.second).at(pos.first) = depth;
    for (unsigned int index = 0; index < allPos.size(); index += 2) {
        x = pos.first + allPos.at(index);
        y = pos.second + allPos.at(index + 1);
        if (x > 0 && y > 0 && x < BOARD_SIZE && y < BOARD_SIZE
        && map.at(y).at(x) != 'X' && (depth < maze.at(y).at(x) || maze.at(y).at(x) == -1)) {
            if (y == target.second && x == target.first) {
                maze.at(y).at(x) = depth + 1;
                return maze;
            }
            maze = findWay(maze, map, depth + 1, std::pair<int, int>(x, y), target);
        }
    }
    return maze;
}


std::vector<std::string> indie::engine::PathFinder::drawCircle(
    std::pair<int, int> pos,
    std::vector<std::vector<int>> maze, std::vector<std::string> map)
{
    std::vector<int> allPos = {1, 0, 0, 1, -1, 0, 0, -1};
    int x = 0;
    int y = 0;
    int save_x = 0;
    int save_y = 0;
    int deptSave = -1;

    maze.at(pos.second).at(pos.first) = -1;
    map.at(pos.second).at(pos.first) = 'o';
    for (unsigned int index = 0; index < allPos.size(); index += 2) {
        x = pos.first + allPos.at(index);
        y = pos.second + allPos.at(index + 1);
        if (x > 0 && y > 0 && x < BOARD_SIZE && y < BOARD_SIZE && maze.at(y).at(x) != -1
        && (deptSave == -1 || deptSave > maze.at(y).at(x))) {
            save_x = x;
            save_y = y;
            deptSave = maze.at(y).at(x);
        }
    }
    if (deptSave == 0) {
        maze.at(save_y).at(save_x) = -1;
        map.at(save_y).at(save_x) = 'o';
        return map;
    }
    if (deptSave == -1)
        return map;
    return drawCircle(std::pair<int, int>(save_x, save_y), maze, map);
}

std::vector<std::vector<int>> indie::engine::PathFinder::initDepthMap()
{
    std::vector<std::vector<int>> map;

    for (int index = 0; index < BOARD_SIZE; index++) {
        map.emplace_back(std::vector<int>());
        for (int idx = 0; idx < BOARD_SIZE; idx++) {
            map.at(index).emplace_back(-1);
        }
    }
    return map;
}