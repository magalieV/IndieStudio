/*
** EPITECH PROJECT, 2019
** temp
** File description:
** temp
*/

#ifndef __BOMBERMAN_MACROINDIE_HPP__
#define __BOMBERMAN_MACROINDIE_HPP__

#include <iostream>
#include <map>

#define MENU_XML "assets/config/menu_object.xml"
#define CONNEXION_XML "assets/config/connexionBoard_object.xml"
#define LOGIN_XML "assets/config/login_object.xml"
#define SIGNUP_XML "assets/config/signup_object.xml"
#define MENU_PLAY_XML "assets/config/menuPlay_object.xml"
#define BOARD_SIZE 15
#define PLAYER_SPEED 3.f

namespace indie::macro {
    enum ButtonSignal {
        _LOGIN,
        _SIGNUP,
        _CONNECT,
        _PLAY,
        _HOW_TO_PLAY,
        _CREDIT,
        _OPTION,
        _MAP,
        _MULTI,
        _QUIT,
        _NEW_GAME,
        _SAVE_1,
        _SAVE_2,
        _SAVE_3,
        _SAVE_4,
        _SAVE_5,
        _OK,
        _DEFAULT
    };
    const std::map<std::string, ButtonSignal> signalString = {
        {"_LOGIN", ButtonSignal::_LOGIN},
        {"_SIGNUP", ButtonSignal::_SIGNUP},
        {"_CONNECT", ButtonSignal::_CONNECT},
        {"_PLAY", ButtonSignal::_PLAY},
        {"_HOW_TO_PLAY", ButtonSignal::_HOW_TO_PLAY},
        {"_CREDIT", ButtonSignal::_CREDIT},
        {"_OPTION", ButtonSignal::_OPTION},
        {"_MAP", ButtonSignal::_MAP},
        {"_MULTI", ButtonSignal::_MULTI},
        {"_QUIT", ButtonSignal::_QUIT},
        {"_NEW_GAME", ButtonSignal::_NEW_GAME},
        {"_SAVE_1", ButtonSignal::_SAVE_1},
        {"_SAVE_2", ButtonSignal::_SAVE_2},
        {"_SAVE_3", ButtonSignal::_SAVE_3},
        {"_SAVE_4", ButtonSignal::_SAVE_4},
        {"_SAVE_5", ButtonSignal::_SAVE_5},
        {"_OK", ButtonSignal::_OK},
    };
    enum MovementManager {_LEFT, _RIGHT, _UPE, _DOWN, _DEFAULT_MOVE, _BOMB};
    enum ArmatureAnimation {_RUN, _STAND, _JUMP, _DEFAULT_ANIM};
    enum PowerUpType {_BOMB_UP = 0, _BOMB_DOWN = 1, _WALL_PASS = 2, _DEFAULT_POWER = 3};
    enum WindowPage{_MENU, _MENU_PLAY, _DEFAULT_PAGE};
}

#endif //__BOMBERMAN_MACROINDIE_HPP__
