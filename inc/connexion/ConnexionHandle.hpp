/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Login
 *
 * File creation = 24/05/2020
 * Last modification = 24/05/2020
 */

#ifndef __BOMBERMAN_CONNEXIONHANDLE_HPP__
#define __BOMBERMAN_CONNEXIONHANDLE_HPP__

#include "connexion/Signup.hpp"
#include "connexion/Login.hpp"
#include "MacroIndie.hpp"
#include <map>
#include <functional>

namespace indie::connexion {
    const std::map<indie::macro::ButtonSignal, std::function<std::unique_ptr<IConnexion>()>> connexionRedirection = {
        {indie::macro::ButtonSignal::_SIGNUP, [](){ return std::unique_ptr<IConnexion>(new Signup()); }},
        {indie::macro::ButtonSignal::_LOGIN, [](){return std::unique_ptr<IConnexion>(new Login() ); }}
    };
}

#endif //__BOMBERMAN_CONNEXIONHANDLE_HPP__