/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = SplashScreen
 *
 * File creation = 14/06/2020
 * Last modification = 14/06/2020
 */

#include "Game/SplashScreen.hpp"

indie::game::SplashScreen::SplashScreen(
    std::shared_ptr<irr::video::IVideoDriver> &videoDriver,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager,
    const std::shared_ptr<irr::gui::IGUIEnvironment> &guiEnvironnement)
{
    _myText = indie::object::Text("3!", irr::video::SColor(255, 255, 255, 255), irr::core::rect<irr::s32>(800, 400, 899, 500), guiEnvironnement);
    _info = indie::object::Text("an explosion lasts on average 5 seconds", irr::video::SColor(255, 255, 255, 255), irr::core::rect<irr::s32>(400, 600, 899, 500), guiEnvironnement);
}

void indie::game::SplashScreen::run(const std::shared_ptr<irr::scene::ISceneManager> &sceneManager, std::shared_ptr<irr::video::IVideoDriver> &videoDriver, indie::object::Window *device)
{
    auto _lastTimer = std::chrono::system_clock::now();
    auto startDab = std::chrono::system_clock::now();
    irr::u32 timeBefore = device->getTime();
    irr::u32 timeNow;
    bool endSplash = false;

    while (device->isRunning()) {
        videoDriver->beginScene(true, true,
                                irr::video::SColor(255, 0, 0, 0));
        auto timer = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = timer - _lastTimer;

        while (elapsed_seconds.count() < 0.020) {
            timer = std::chrono::system_clock::now();
            elapsed_seconds = timer - _lastTimer;
        }
        timeNow = device->getTime();
        const irr::f32 framerate = (irr::f32)(timeNow - timeBefore) / 1000.f;
        if (framerate < 1) {
            _myText.draw(videoDriver);
        } else if (framerate >= 1 && framerate < 2) {
            _myText.setText("2!");
            _myText.draw(videoDriver);
        } else if (framerate >= 2 && framerate < 3) {
            _myText.setText("1!");
            _myText.draw(videoDriver);
        } else if (framerate >= 3 && framerate < 4) {
            _myText.setText("GO!");
            _myText.draw(videoDriver);
        } else if (framerate > 4) {
            endSplash = true;
        }
        _info.draw(videoDriver);
        videoDriver->endScene();
        if (endSplash)
            return;
    }
}