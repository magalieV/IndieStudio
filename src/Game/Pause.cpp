/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Pause
 *
 * File creation = 12/06/2020
 * Last modification = 12/06/2020
 */

#include "Game/Pause.hpp"

indie::game::Pause::Pause(
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    std::shared_ptr<irr::video::IVideoDriver> videoDriver,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement, bool save)
{
    _pictureBank.add(indie::object::Picture("assets/game/pause/back.png", std::pair<float, float>(610, 140), std::pair<float, float>(700, 800), videoDriver));
    if (save)
        _buttonBank.addButton(indie::object::Button("Save", "Save the game", indie::object::Button::info_t(irr::core::rect<irr::s32>(940, 240, 1340, 438), indie::macro::_SAVE_1), guiEnvironnement, videoDriver));
    _buttonBank.addButton(indie::object::Button("Quit", "Quit the game", indie::object::Button::info_t(irr::core::rect<irr::s32>(940, 616, 1340, 814), indie::macro::_QUIT), guiEnvironnement, videoDriver));
    _objectBank.addObject(&_pictureBank);
    _objectBank.addObject(&_buttonBank);
}

indie::macro::ButtonSignal indie::game::Pause::draw(std::shared_ptr<irr::video::IVideoDriver> &videoDriver)
{
    indie::macro::ButtonSignal signal = indie::macro::ButtonSignal::_DEFAULT;

    _objectBank.draw(videoDriver);
    signal = _buttonBank.handleEvent();
    return signal;
}