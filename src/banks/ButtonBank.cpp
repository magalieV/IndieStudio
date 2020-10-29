/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = ButtonBank
 *
 * File creation = 24/05/2020
 * Last modification = 24/05/2020
 */

#include "banks/ButtonBank.hpp"
#include "../../EncryptTool/inc/Decryption.hpp"
#include "../../EncryptTool/inc/XMLReader.hpp"
#include <map>

indie::macro::ButtonSignal indie::bank::ButtonBank::handleEvent() const
{
    for (const auto &button : _buttonList) {
        if (button.isPressed())
            return button.getSignal();
    }
    return indie::macro::ButtonSignal::_DEFAULT;
}

void indie::bank::ButtonBank::addButton(indie::object::Button button)
{
    _buttonList.emplace_back(button);
}

void indie::bank::ButtonBank::draw(std::shared_ptr<irr::video::IVideoDriver> &driver)
{
    for (auto &button : _buttonList) {
        button.draw(driver);
    }
}

void indie::bank::ButtonBank::addButton(std::shared_ptr<irr::video::IVideoDriver> &driver,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
    const std::map<std::string, std::string> info)
{
    indie::macro::ButtonSignal signal = indie::macro::ButtonSignal::_DEFAULT;
    std::vector<std::string> tmp = XMLReader::splitString(";", info.at("upperLeft"));
    std::pair<int, int> upper(std::stoi(tmp.at(0)), std::stoi(tmp.at(1)));
    tmp = XMLReader::splitString(";", info.at("lowerRight"));
    std::pair<int, int> lower(std::stoi(tmp.at(0)), std::stoi(tmp.at(1)));

    for (const auto &str : indie::macro::signalString) {
        if (str.first == info.at("signal")) {
            signal = str.second;
            break;
        }
    }
    this->addButton(indie::object::Button(info.at("text"), info.at("about"),
    indie::object::Button::info_t(irr::core::rect<irr::s32>(upper.first,
    upper.second, lower.first, lower.second), signal, info.at("normal"),
    info.at("hover"), info.at("pressed")), guiEnvironnement, driver));
}

void indie::bank::ButtonBank::addButton(const std::string &configFile,
    std::shared_ptr<irr::video::IVideoDriver> &driver,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    std::list<std::string> content = encrypt::Decryption::stringFromFile(configFile);
    std::list<std::vector<std::string> > button = XMLReader::getGroup("<buttons>", "</buttons>", content);
    std::map<std::string, std::string> infoButton;

    for (const auto &value : button) {
        if (value[0] == "/button") {
            this->addButton(driver, guiEnvironnement, infoButton);
            infoButton.clear();
        } else if (value[0] != "/buttons" && value[0] != "button" && value[0] != "buttons") {
            infoButton[value[0]] = value[1];
        }
    }
}