/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Core
 *
 * File creation = 06/06/2020
 * Last modification = 06/06/2020
 */

#include <objects/Music.hpp>
#include <menu/Menu.hpp>
#include <connexion/ConnexionBoard.hpp>
#include <thread>
#include "Engine/Core.hpp"
#include "objects/StaticObject.hpp"
#include "Game/Intro.hpp"

indie::engine::Core::Core()
{
    _device = new indie::object::Window("Bomberman",
        std::pair<float, float>(1920, 1080), 32);
}

indie::engine::Core::~Core()
{
    _device->drop();
}

void indie::engine::Core::run() const
{
  run_menu();
}

void indie::engine::Core::run_menu() const
{
    indie::object::Music music("assets/menu/menu_sound.ogg");
    std::shared_ptr<irr::gui::IGUIEnvironment> guiEnv = _device->getGuiEnvironement();
    std::shared_ptr<irr::video::IVideoDriver> videoDriver = _device->getVideoDriver();
    std::shared_ptr<irr::scene::ISceneManager> sceneManager = _device->getSceneManager();
    indie::game::Intro intro(videoDriver, sceneManager, guiEnv);
    indie::object::Music musicIntro("assets/intro.ogg");

    music.setVolume(100);
    musicIntro.play();
    intro.run(sceneManager, videoDriver, _device);
    sceneManager->clear();
    guiEnv->clear();
    musicIntro.stop();
    indie::connexion::ConnexionBoard connexionBoard(videoDriver, guiEnv);
    music.play();
    videoDriver->enableMaterial2D(true);
    connexionBoard.run(videoDriver, _device, guiEnv);
    sceneManager->clear();
    guiEnv->clear();
    indie::menu::Menu menu(videoDriver, guiEnv, sceneManager);
    menu.run(videoDriver, _device, guiEnv, sceneManager);
    music.stop();
}

void indie::engine::Core::run_game() const
{
}