/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Login
 *
 * File creation = 24/05/2020
 * Last modification = 24/05/2020
 */

#include "connexion/Login.hpp"
#include "../EncryptTool/inc/Decryption.hpp"
#include "../EncryptTool/inc/XMLReader.hpp"

indie::connexion::Login::Login()
= default;

void indie::connexion::Login::init(std::shared_ptr<irr::video::IVideoDriver> &driver,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    std::list<std::string> content = encrypt::Decryption::stringFromFile(_userFile);
    std::list<std::vector<std::string> > userList = XMLReader::getGroup("<user>", "</user>", content);
    std::string tmp;

    _pictureBank.add(LOGIN_XML, driver, guiEnvironnement);
    _buttonBank.addButton(LOGIN_XML, driver, guiEnvironnement);
    _formsBank.add(LOGIN_XML, driver, guiEnvironnement);
    _objectBank.addObject(&_pictureBank);
    _objectBank.addObject(&_buttonBank);
    _objectBank.addObject(&_formsBank);
    for (const auto &value : userList) {
        if (value[0] == _password) {
            tmp = value[1];
        } else if (value[0] == _username && !tmp.empty()) {
            _userList[value[1]] = tmp;
            tmp.clear();
        } else if (value[0] != "user") {
            return;
        }
    }
}

bool indie::connexion::Login::checkIfExist(const std::string &username, const std::string &password)
{
    for (const auto &account : _userList) {
        if (account.first == username && account.second == password)
            return true;
    }
    return false;
}

void indie::connexion::Login::run(std::shared_ptr<irr::video::IVideoDriver> &driver, indie::object::Window *device, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    indie::macro::ButtonSignal buttonPressedSignal = indie::macro::ButtonSignal::_DEFAULT;
    bool drawInvalidPass = false;
    std::map<std::string, std::string> inputs;
    indie::object::Text errorDisplay("Warning: invalid account", irr::video::SColor(255,179,0,0), irr::core::rect<irr::s32>(540,135,833,160), guiEnvironnement);

    while (device->isRunning()) {
        driver->beginScene(true, true, irr::video::SColor (0,255,255,255));
        _objectBank.draw(driver);
        buttonPressedSignal = _buttonBank.handleEvent();
        if (buttonPressedSignal == indie::macro::ButtonSignal::_CONNECT) {
            drawInvalidPass = false;
            inputs = _formsBank.getInputs();
            if (inputs.find("username") != inputs.end() &&
            inputs.find("password") != inputs.end() && checkIfExist(inputs.at("username"), inputs.at("password"))) {
                device->setUserName(inputs.at("username"));
                break;
            }
            else
                drawInvalidPass = true;
        }
        if (drawInvalidPass)
            errorDisplay.draw(driver);
        device->drawMouseAnimation(driver);
        driver->endScene();
    }
}