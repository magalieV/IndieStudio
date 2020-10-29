/*
 * Project Name = bomberman
 *
 * Author = magalie.vandenbriele | irama.chaouch | theodore.faraut-schwieg
 * | paul.riba | cesar.venzac
 * Object = Window
 *
 * File creation = 22/05/2020
 * Last modification = 22/05/2020
 */

#include "Engine/Window.hpp"

indie::object::Window::Window(const std::string &name,
    const std::pair<float, float> &dimension, unsigned int bits)
{
    std::wstring windowName = std::wstring(name.begin(), name.end());
    irr::IrrlichtDevice *nulldevice = irr::createDevice(irr::video::EDT_NULL);
    irr::core::dimension2d<irr::u32> screenSize = nulldevice->getVideoModeList()->getDesktopResolution();

    nulldevice->drop();
    if (screenSize.Height > 1080)
        screenSize.Height = 1080;
    if (screenSize.Width > 1920)
        screenSize.Width = 1920;
    _device = std::shared_ptr<irr::IrrlichtDevice>(irr::createDevice(irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(screenSize.Width, screenSize.Height), bits,
        false, false));
    if (_device) {
        _videoDriver = std::shared_ptr<irr::video::IVideoDriver>(_device->getVideoDriver());
        _sceneManager = std::shared_ptr<irr::scene::ISceneManager>(_device->getSceneManager());
        _guiEnvironnement = std::shared_ptr<irr::gui::IGUIEnvironment>(_device->getGUIEnvironment());
        _device->setWindowCaption(windowName.c_str());
    }
    _eventHandler = new indie::engine::EventHandler(_device.get(), _videoDriver);
    _device->setEventReceiver(_eventHandler);
    _mouseAnimation = new indie::object::Animation("assets/mouse_animation/blood_anim.png",
        std::pair<float, float>(0, 0),
        std::pair<float, float>(3000, 250),
        _videoDriver,
        250, 12);
    _device->getVideoDriver()->setMaterial(_device->getVideoDriver()->getMaterial2D());
}

indie::object::Window::~Window()
{

}

bool    indie::object::Window::windowExist() const
{
    if (!_device)
        return false;
    return true;
}

bool    indie::object::Window::isRunning() const
{
    return _device->run();
}

void    indie::object::Window::drop() const
{
    _device->drop();
}

std::shared_ptr<irr::scene::ISceneManager>  indie::object::Window::getSceneManager() const
{
    return _sceneManager;
}

std::shared_ptr<irr::video::IVideoDriver>   indie::object::Window::getVideoDriver() const
{
    return _videoDriver;
}

std::shared_ptr<irr::gui::IGUIEnvironment>  indie::object::Window::getGuiEnvironement() const
{
    return _guiEnvironnement;
}

bool    indie::object::Window::isActive() const
{
    return _device->isWindowActive();
}

void    indie::object::Window::closeDevice()
{
    _device->closeDevice();
}

void indie::object::Window::drawMouseAnimation(std::shared_ptr<irr::video::IVideoDriver> &driver)
{
    if (_eventHandler->get_mouseClicked()) {
        irr::core::vector2d<irr::s32> pos = _eventHandler->get_mousePosition();
        _mouseAnimation->setCanDraw();
        pos.X -= 125;
        pos.Y -= 125;
        _mouseAnimation->setPosition(pos);
    }
    _mouseAnimation->draw(driver);
}

irr::EKEY_CODE indie::object::Window::getLastKeyPressed()
{
    return _eventHandler->getLastKeyPressed();
}

irr::EKEY_CODE indie::object::Window::getLastKeyReleased()
{
    return _eventHandler->getLastKeyReleased();
}

irr::u32 indie::object::Window::getTime() const
{
    return _device->getTimer()->getTime();
}

irr::core::dimension2d<irr::u32> indie::object::Window::getScreenSize()
{
    return _device->getVideoModeList()->getDesktopResolution();
}


void indie::object::Window::setUserName(const std::string &name)
{
    _userName = name;
}

std::string indie::object::Window::getUserName() const
{
    return _userName;
}