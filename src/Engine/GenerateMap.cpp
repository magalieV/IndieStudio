/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = GenerateMap
 *
 * File creation = 07/06/2020
 * Last modification = 07/06/2020
 */

#include "Engine/GenerateMap.hpp"
#include "MacroIndie.hpp"
#include <ctime>

std::vector<std::string> indie::engine::GenerateMap::generate()
{
    std::pair<int, int> info(BOARD_SIZE, BOARD_SIZE);
    std::vector<std::string> labyrinth = createMap(info);

    std::srand(std::time(0));
    labyrinth = createPath(labyrinth);
    labyrinth = concatLabyrinth(labyrinth);
    labyrinth = putHorizontalWall(labyrinth);
    std::vector<int> moovePosOne = {1, 2, 1, 3, 2, 1, 3, 1};
    for (int idx = 0; idx < moovePosOne.size(); idx+=2)
        labyrinth.at(moovePosOne.at(idx + 1)).at(moovePosOne.at(idx)) = '*';
    std::vector<int> moovePosTwo = {1, BOARD_SIZE - 3, 1, BOARD_SIZE - 4, 2, BOARD_SIZE - 2, 3, BOARD_SIZE - 2};
    for (int idx = 0; idx < moovePosTwo.size(); idx+=2)
        labyrinth.at(moovePosTwo.at(idx + 1)).at(moovePosTwo.at(idx)) = '*';
    std::vector<int> moovePosThree = {BOARD_SIZE - 3, 1, BOARD_SIZE - 4, 1, BOARD_SIZE - 2, 2, BOARD_SIZE - 2, 3};
    for (int idx = 0; idx < moovePosThree.size(); idx+=2)
        labyrinth.at(moovePosThree.at(idx + 1)).at(moovePosThree.at(idx)) = '*';
    std::vector<int> moovePosFour = {BOARD_SIZE - 2, BOARD_SIZE - 3, BOARD_SIZE - 2, BOARD_SIZE - 4, BOARD_SIZE - 3, BOARD_SIZE - 2, BOARD_SIZE - 4, BOARD_SIZE - 2};
    for (int idx = 0; idx < moovePosFour.size(); idx+=2)
        labyrinth.at(moovePosFour.at(idx + 1)).at(moovePosFour.at(idx)) = '*';
    std::vector<int> finalPos = {1, 1, BOARD_SIZE - 2, 1, 1, BOARD_SIZE - 2, BOARD_SIZE - 2, BOARD_SIZE - 2};
    for (int idx = 0; idx < finalPos.size(); idx+=2)
        labyrinth.at(finalPos.at(idx + 1)).at(finalPos.at(idx)) = '*';
    return labyrinth;
}

std::vector<std::string> indie::engine::GenerateMap::createMap(std::pair<int, int> size)
{
    std::vector<std::string> map;

    for (unsigned int index = 0; index < size.second; index++) {
        map.emplace_back(std::string(""));
        for (unsigned int idx = 0; idx < size.second; idx++) {
            map.at(index).push_back('X');
        }
    }
    return map;
}

std::vector<std::string> indie::engine::GenerateMap::createPath(std::vector<std::string> map)
{
    std::pair<int, int> pos(1, 1);
    int save_x = 0;
    int save_y = 0;
    std::vector<std::pair<int, int>> historic;
    int index = -1;
    bool begin = true;

    map.at(pos.second).at(pos.first) = '*';
    while (pos.first != 1 || pos.second != 1 || begin) {
        save_x = pos.first;
        save_y = pos.second;
        begin = false;
        pos = choosePosPath(map, pos);
        if (pos.first == save_x && pos.second == save_y && index - 1 <= 0) {
            break;
        } else if (pos.first == save_x && pos.second == save_y) {
            index--;
            pos = historic.at(index);
            historic.pop_back();
        } else {
            historic.emplace_back(std::pair<int, int>(save_x, save_y));
            index++;
        }
        map.at(pos.second).at(pos.first) = '*';
    }
    return map;
}

std::pair<int, int> indie::engine::GenerateMap::choosePosPath(std::vector<std::string> labyrinth, std::pair<int, int> pos)
{
    int my_rand = std::rand() % 4 + 1;
    std::pair<int, int> newPos;
    std::vector<std::pair<int, int>> historic;
    bool foundHisto = true;

    while (true) {
        foundHisto = true;
        while (foundHisto) {
            my_rand = std::rand() % 4 + 1;
            switch (my_rand) {
                case 1:
                    newPos.first = pos.first;
                    newPos.second = pos.second - 1;
                    break;
                case 2:
                    newPos.first = pos.first;
                    newPos.second = pos.second + 1;
                    break;
                case 3:
                    newPos.first = pos.first - 1;
                    newPos.second = pos.second;
                    break;
                default:
                    newPos.first = pos.first + 1;
                    newPos.second = pos.second;
                    break;
            }
            foundHisto = false;
            for (const auto &his : historic) {
                if (his == newPos)
                    foundHisto = true;
            }
        }
        historic.emplace_back(newPos);
        if (labyrinth.size() - 1 > newPos.second && newPos.first > 0 && newPos.second > 0 &&
            labyrinth.at(0).size() - 1 > newPos.first
            && checkAround(labyrinth, newPos, pos) &&
            labyrinth.at(newPos.second).at(newPos.first) != '*') {
            return (newPos);
        }
        if (historic.size() >= 4)
            break;
    }
    return pos;
}

bool indie::engine::GenerateMap::checkAround(std::vector<std::string> map,
    std::pair<int, int> pos, std::pair<int, int> lastPos)
{
    std::vector<int> moove = {1, 0, 0, 1, -1, 0, 0, -1};
    int x_tmp = 0;
    int y_tmp = 0;

    for (int i = 0; i < 8; i++) {
        x_tmp = pos.first + moove[i];
        y_tmp = pos.second + moove[i + 1];
        if ((x_tmp != lastPos.first || y_tmp != lastPos.second)
            && map.size() - 1 > y_tmp && map.at(0).size() - 1 > x_tmp
            && map.at(y_tmp).at(x_tmp) == '*')
            return (false);
        i += 1;
    }
    return (true);
}

unsigned int indie::engine::GenerateMap::countAround(
    std::vector<std::string> map, std::pair<int, int> pos)
{
    unsigned int count = 0;
    std::vector<int> moove = {1, 0, 0, 1, -1, 0, 0, -1};
    int x_tmp = 0;
    int y_tmp = 0;

    for (int i = 0; i < 8; i++) {
        x_tmp = pos.first + moove[i];
        y_tmp = pos.second + moove[i + 1];
        if (map.size() - 1 > y_tmp && map.at(0).size() - 1 > x_tmp
            && map.at(y_tmp).at(x_tmp) == 'X')
            count++;
        i += 1;
    }
    return (count);
}

std::vector<std::string> indie::engine::GenerateMap::putHorizontalWall(
    std::vector<std::string> map)
{
    int myRand;

    for (unsigned int index = 0; index < map.size(); index++) {
        for (unsigned int idx = 0; idx < map.at(index).size(); idx++) {
            if (map.at(index).at(idx) == '*' && index != 1 && idx != 1) {
                myRand = std::rand() % 4 + 1;
                if (myRand == 1) {
                    map.at(index).at(idx) = 'Z';
                }
                myRand = std::rand() % 13 + 1;
                if (myRand == 1) {
                    map.at(index).at(idx) = 'Z';
                }
            }
        }
    }
    return map;
}

std::vector<std::string> indie::engine::GenerateMap::concatLabyrinth(
    std::vector<std::string> first)
{
    std::pair<int, int> info(BOARD_SIZE, BOARD_SIZE);
    std::vector<std::string> new_labyrinth = createMap(info);
    unsigned int count = 0;

    for (unsigned int index = 0; index < first.size(); index++) {
        for (unsigned int idx = 0; idx < first.at(index).size(); idx++) {
            if (first.at(index).at(idx) == 'X' && idx != 0 && index != 0 && idx < first.at(index).size() - 1 && index < first.size() - 1) {
                count = countAround(first, std::pair<int, int>(idx, index));
                if (count >= 3) {
                    new_labyrinth.at(index).at(idx) = '*';
                    first.at(index).at(idx) = '*';
                } else {
                    new_labyrinth.at(index).at(idx) = first.at(index).at(idx);
                }
            } else {
                new_labyrinth.at(index).at(idx) = first.at(index).at(idx);
            }
        }
    }
    return (new_labyrinth);
}