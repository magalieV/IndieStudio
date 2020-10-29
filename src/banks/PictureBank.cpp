/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = PictureBank
 *
 * File creation = 04/06/2020
 * Last modification = 04/06/2020
 */

#include "banks/PictureBank.hpp"
#include "../../EncryptTool/inc/Decryption.hpp"
#include "../../EncryptTool/inc/XMLReader.hpp"

void indie::bank::PictureBank::add(indie::object::Picture button)
{
    _pictureList.emplace_back(button);
}

void indie::bank::PictureBank::draw(std::shared_ptr<irr::video::IVideoDriver> &driver)
{
    for (auto &pic : _pictureList) {
        pic.draw(driver);
    }
}

void indie::bank::PictureBank::add(std::shared_ptr<irr::video::IVideoDriver> &driver,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
    const std::map<std::string, std::string> info)
{
    std::vector<std::string> tmp = XMLReader::splitString(";", info.at("position"));
    std::pair<float, float> pos(std::stof(tmp.at(0)), std::stof(tmp.at(1)));
    tmp = XMLReader::splitString(";", info.at("size"));
    std::pair<float, float> size(std::stof(tmp.at(0)), std::stof(tmp.at(1)));

    this->add(indie::object::Picture(info.at("path"), pos, size, driver));
}

void indie::bank::PictureBank::add(const std::string &configFile,
    std::shared_ptr<irr::video::IVideoDriver> &driver,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    std::list<std::string> content = encrypt::Decryption::stringFromFile(configFile);
    std::list<std::vector<std::string> > button = XMLReader::getGroup("<pictures>", "</pictures>", content);
    std::map<std::string, std::string> infoButton;

    for (const auto &value : button) {
        if (value[0] == "/picture") {
            this->add(driver, guiEnvironnement, infoButton);
            infoButton.clear();
        } else if (value[0] != "/pictures" && value[0] != "picture" && value[0] != "pictures") {
            infoButton[value[0]] = value[1];
        }
    }
}