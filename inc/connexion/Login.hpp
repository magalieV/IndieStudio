/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Login
 *
 * File creation = 24/05/2020
 * Last modification = 24/05/2020
 */

#ifndef __BOMBERMAN_LOGIN_HPP__
#define __BOMBERMAN_LOGIN_HPP__

#include "interface/IConnexion.hpp"
#include "banks/ButtonBank.hpp"
#include "banks/PictureBank.hpp"
#include "banks/ObjectBank.hpp"
#include "banks/FormBank.hpp"
#include <map>

namespace indie::connexion {
    class Login : public indie::connexion::IConnexion {
        public:
            Login();
            ~Login() final = default;
            void init(std::shared_ptr<irr::video::IVideoDriver> &driver,
                      const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement) final;
            void run(std::shared_ptr<irr::video::IVideoDriver> &driver,
                indie::object::Window *device, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement) final;
            bool checkIfExist(const std::string &username, const std::string &password);
        private:
            indie::bank::PictureBank _pictureBank;
            indie::bank::ObjectBank _objectBank;
            indie::bank::FormBank _formsBank;
            indie::bank::ButtonBank _buttonBank;
            std::map<std::string, std::string> _userList;
            const std::string _username = "username";
            const std::string _password = "password";
            const std::string _userFile = ".save/.users/.userAccount.xml";
    };
}

#endif //__BOMBERMAN_LOGIN_HPP__
