/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = FormBank
 *
 * File creation = 04/06/2020
 * Last modification = 04/06/2020
 */

#include "banks/FormBank.hpp"
#include "../../EncryptTool/inc/Decryption.hpp"
#include "../../EncryptTool/inc/XMLReader.hpp"

void indie::bank::FormBank::add(indie::object::Form form, const std::string &name)
{
    _forms[name] = form;
}

void indie::bank::FormBank::draw(std::shared_ptr<irr::video::IVideoDriver> &driver)
{
    for (auto &form : _forms) {
        form.second.draw(driver);
    }
}

std::map<std::string, std::string> indie::bank::FormBank::getInputs() const
{
    std::map<std::string, std::string> inputs;

    for (const auto &form : _forms) {
        if (!form.second.getInput().empty())
            inputs[form.first] = form.second.getInput();
    }
    return inputs;
}

void indie::bank::FormBank::add(const std::string &configFile,
    std::shared_ptr<irr::video::IVideoDriver> &driver,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    std::list<std::string> content = encrypt::Decryption::stringFromFile(configFile);
    std::list<std::vector<std::string> > button = XMLReader::getGroup("<forms>", "</forms>", content);
    std::map<std::string, std::string> infoButton;

    for (const auto &value : button) {
        if (value[0] == "/form") {
            this->add(driver, guiEnvironnement, infoButton);
            infoButton.clear();
        } else if (value[0] != "/forms" && value[0] != "form" && value[0] != "forms") {
            infoButton[value[0]] = value[1];
        }
    }
}

void indie::bank::FormBank::add(std::shared_ptr<irr::video::IVideoDriver> &driver,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement,
    const std::map<std::string, std::string> info)
{
    std::vector<std::string> tmp = XMLReader::splitString(";", info.at("pos"));
    irr::core::rect<irr::s32> pos;
    irr::video::SColor boxColor;
    irr::video::SColor textColor;
    bool pass = false;

    pos.UpperLeftCorner.X = std::stof(tmp[0]);
    pos.UpperLeftCorner.Y = std::stof(tmp[1]);
    pos.LowerRightCorner.X = std::stof(tmp[2]);
    pos.LowerRightCorner.Y = std::stof(tmp[3]);
    tmp = XMLReader::splitString(";", info.at("box_color"));
    boxColor = irr::video::SColor(std::stof(tmp[0]), std::stof(tmp[1]), std::stof(tmp[2]), std::stof(tmp[3]));
    tmp = XMLReader::splitString(";", info.at("text_color"));
    textColor = irr::video::SColor(std::stof(tmp[0]), std::stof(tmp[1]), std::stof(tmp[2]), std::stof(tmp[3]));
    if (info.at("password") == "true")
        pass = true;
    this->add(indie::object::Form(pos, std::stoi(info.at("size")), guiEnvironnement, info.at("text"),
        boxColor, textColor, pass, info.at("font")), info.at("name"));
}