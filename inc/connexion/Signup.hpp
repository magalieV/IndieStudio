/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Signin
 *
 * File creation = 24/05/2020
 * Last modification = 24/05/2020
 */

#ifndef __BOMBERMAN_SIGNIN_HPP__
#define __BOMBERMAN_SIGNIN_HPP__

#include <banks/PictureBank.hpp>
#include "interface/IConnexion.hpp"
#include "../EncryptTool/inc/XMLReader.hpp"
#include "banks/ButtonBank.hpp"
#include "banks/ObjectBank.hpp"
#include "banks/FormBank.hpp"

namespace indie::connexion {
    class Signup : public indie::connexion::IConnexion {
        public:
            Signup();
            ~Signup() final = default;
            void init(std::shared_ptr<irr::video::IVideoDriver> &driver,
                const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement) final;
            void run(std::shared_ptr<irr::video::IVideoDriver> &driver,
                indie::object::Window *device, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement) final;
            bool exist(const std::string &userName);
            void addUser(const std::string &userName, const std::string &password);
        private:
            indie::bank::PictureBank _pictureBank;
            indie::bank::ButtonBank _buttonBank;
            indie::bank::ObjectBank _objectBank;
            indie::bank::FormBank _formsBank;
            XMLReader _reader;
            std::map<std::string, std::string> _userList;
            const std::string _username = "username";
            const std::string _password = "password";
            const std::string _userFile = ".save/.users/.userAccount.xml";
    };
}

#endif //__BOMBERMAN_SIGNIN_HPP__
