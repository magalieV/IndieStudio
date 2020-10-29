/*
 * Project Name = bomberman
 *
 * Author = magalie.vandenbriele | irama.chaouch | theodore.faraut-schwieg
 * | paul.riba | cesar.venzac
 * Object = ConnexionBoard
 *
 * File creation = 22/05/2020
 * Last modification = 22/05/2020
 */

#include <connexion/ConnexionHandle.hpp>
#include "connexion/ConnexionBoard.hpp"
#include "MacroIndie.hpp"

indie::connexion::ConnexionBoard::ConnexionBoard(std::shared_ptr<irr::video::IVideoDriver> &driver,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    _pictureBank.add(CONNEXION_XML, driver, guiEnvironnement);
    _buttonBank.addButton(CONNEXION_XML, driver, guiEnvironnement);
    _objectBank.addObject(&_pictureBank);
    _objectBank.addObject(&_buttonBank);
}

indie::connexion::ConnexionBoard::~ConnexionBoard()
{

}

void    indie::connexion::ConnexionBoard::run(std::shared_ptr<irr::video::IVideoDriver> &driver,
    indie::object::Window *device, const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    indie::macro::ButtonSignal buttonPressedSignal = indie::macro::ButtonSignal::_DEFAULT;

    while (device->isRunning()) {
        driver->beginScene(true, true, irr::video::SColor(0,255,255,255));
        _objectBank.draw(driver);
        device->drawMouseAnimation(driver);
        buttonPressedSignal = _buttonBank.handleEvent();
        driver->endScene();
        if (buttonPressedSignal != indie::macro::ButtonSignal::_DEFAULT)
            break;
    }
    if (indie::connexion::connexionRedirection.find(buttonPressedSignal) == indie::connexion::connexionRedirection.end())
        return;
    std::unique_ptr<IConnexion> nextPage = connexionRedirection.at(buttonPressedSignal)();
    nextPage->init(driver, guiEnvironnement);
    nextPage->run(driver, device, guiEnvironnement);
}