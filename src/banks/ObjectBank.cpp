/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = ObjectBank
 *
 * File creation = 03/06/2020
 * Last modification = 03/06/2020
 */

#include "banks/ObjectBank.hpp"

void indie::bank::ObjectBank::addObject(indie::object::IVisualObject *object)
{
    _objectList.emplace_back(object);
    _lastTimer = std::chrono::system_clock::now();
}

void indie::bank::ObjectBank::draw(std::shared_ptr<irr::video::IVideoDriver> &driver)
{
    auto timer = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = timer - _lastTimer;

    while (elapsed_seconds.count() < 0.020) {
        timer = std::chrono::system_clock::now();
        elapsed_seconds = timer - _lastTimer;
    }
    _lastTimer = std::chrono::system_clock::now();
    for (const auto &obj : _objectList) {
        obj->draw(driver);
    }
}