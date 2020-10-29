/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = EventHandler
 *
 * File creation = 06/06/2020
 * Last modification = 06/06/2020
 */

#ifndef __BOMBERMAN_EVENTHANDLER_HPP__
#define __BOMBERMAN_EVENTHANDLER_HPP__

#include <memory>
#include <IEventReceiver.h>
#include <IrrlichtDevice.h>
#include <IAnimatedMeshSceneNode.h>
#include <map>

namespace indie::engine {
    class EventHandler : public irr::IEventReceiver {
        public:
            EventHandler() = delete;
            EventHandler(irr::IrrlichtDevice *device, std::shared_ptr<irr::video::IVideoDriver> &driver);
            bool OnEvent(const irr::SEvent &event);
            [[nodiscard]] irr::core::vector2d<irr::s32> get_mousePosition() const;
            bool get_mouseClicked();
            irr::EKEY_CODE getLastKeyPressed();
            irr::EKEY_CODE getLastKeyReleased();
            bool isKeyPressed(const irr::EKEY_CODE &key);
            bool isKeyReleased(const irr::EKEY_CODE &key);
        private:
            irr::IrrlichtDevice *_device;
            bool _isClicked;
            irr::core::vector2d<irr::s32> _mousePosition;
            irr::EKEY_CODE _lastKeyPush;
            irr::EKEY_CODE _lastKeyReleased;
            irr::scene::IAnimatedMeshSceneNode *_mesh;
            std::map<irr::u32, bool> _iskeyPressed;
            std::map<irr::u32, bool> _iskeyReleased;
    };
}

#endif //__BOMBERMAN_EVENTHANDLER_HPP__
