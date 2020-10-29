/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Signin
 *
 * File creation = 24/05/2020
 * Last modification = 24/05/2020
 */

#include <filesystem>
#include "connexion/Signup.hpp"
#include "../EncryptTool/inc/Decryption.hpp"
#include "../EncryptTool/inc/Encryption.hpp"
#include "MacroIndie.hpp"

indie::connexion::Signup::Signup()
= default;

void indie::connexion::Signup::init(std::shared_ptr<irr::video::IVideoDriver> &driver, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    std::list<std::string> content = encrypt::Decryption::stringFromFile(_userFile);
    std::list<std::vector<std::string> > userList = XMLReader::getGroup("<user>", "</user>", content);
    std::string tmp;

    _pictureBank.add(SIGNUP_XML, driver, guiEnvironnement);
    _buttonBank.addButton(SIGNUP_XML, driver, guiEnvironnement);
    _formsBank.add( SIGNUP_XML, driver, guiEnvironnement);
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

bool indie::connexion::Signup::exist(const std::string &username)
{
    for (const auto &account : _userList) {
        if (account.first == username)
            return true;
    }
    return false;
}

void indie::connexion::Signup::addUser(const std::string &username, const std::string &password)
{
    std::map<std::string, std::string> accountInfo;
    std::list<std::string> content;

    _reader.clearFile();
    _reader.startGroup("account");
    for (const auto &account : _userList) {
        _reader.startGroup("user");
        accountInfo.clear();
        accountInfo["username"] = account.first;
        accountInfo["password"] = account.second;
        _reader.writeInfo(accountInfo);
        _reader.endGroup("user");
    }
    _reader.startGroup("user");
    accountInfo.clear();
    accountInfo["username"] = username;
    accountInfo["password"] = password;
    _reader.writeInfo(accountInfo);
    _reader.endGroup("user");
    _reader.endGroup("account");
    content = _reader.getContent();
    encrypt::Encryption::fileFromString(content, _userFile);
    std::filesystem::create_directory(".save/.users/." + username + "_save");
}

void indie::connexion::Signup::run(std::shared_ptr<irr::video::IVideoDriver> &driver, indie::object::Window *device, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    indie::macro::ButtonSignal buttonPressedSignal = indie::macro::ButtonSignal::_DEFAULT;
    std::map<std::string, std::string> inputs;
    indie::object::Text errorDisplay("None", irr::video::SColor(255,179,0,0), irr::core::rect<irr::s32>(540,135,833,160), guiEnvironnement);
    bool drawInvalidPass = false;

    while (device->isRunning()) {
        driver->beginScene(true, true, irr::video::SColor (0,255,255,255));
        _objectBank.draw(driver);
        buttonPressedSignal = _buttonBank.handleEvent();
        if (buttonPressedSignal == indie::macro::ButtonSignal::_CONNECT) {
            drawInvalidPass = false;
            inputs = _formsBank.getInputs();
            if (inputs.find("password") != inputs.end() &&
                inputs.find("password conf") != inputs.end() && inputs.at("password") != inputs.at("password conf")) {
                drawInvalidPass = true;
                errorDisplay.setText("Error: The password doesn't match");
            } else if (inputs.find("username") != inputs.end() && exist(inputs.at("username"))) {
                drawInvalidPass = true;
                errorDisplay.setText("Error: The username already exist!");
            } else if (inputs.size() != 3) {
                drawInvalidPass = true;
                errorDisplay.setText("Error: You must fill all the info");
            } else if (inputs.find("username") != inputs.end() && inputs.find("password") != inputs.end()
            && inputs.find("password conf") != inputs.end()){
                addUser(inputs.at("username"), inputs.at("password"));
                device->setUserName(inputs.at("username"));
                break;
            }
        }
        if (drawInvalidPass)
            errorDisplay.draw(driver);
        device->drawMouseAnimation(driver);
        driver->endScene();
    }
}