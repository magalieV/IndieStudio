/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Animation
 *
 * File creation = 27/05/2020
 * Last modification = 27/05/2020
 */

#ifndef __BOMBERMAN_ANIMATION_HPP__
#define __BOMBERMAN_ANIMATION_HPP__

#include "Picture.hpp"
#include "interface/IVisualObject.hpp"

namespace indie::object {
    class Animation : public IVisualObject {
        public:
            Animation() = default;
            Animation(const Animation &other);
            Animation& operator=(const Animation &other);
            Animation(const std::string &picturePath,
            const std::pair<float, float> &position,
            const std::pair<float, float> &size,
                std::shared_ptr<irr::video::IVideoDriver> &driver,
                float frameSize, unsigned int frameNumber);
            void draw(std::shared_ptr<irr::video::IVideoDriver> &driver) final;
            void setPosition(irr::core::position2d<irr::s32> newPosition);
            void reini();
            void setCanDraw();
            bool canDraw();

        private:
            indie::object::Picture _picture;
            unsigned int _actualFrame;
            unsigned int _totalFrame;
            float _frameSize;
            bool _canDraw;
    };
}

#endif //__BOMBERMAN_ANIMATION_HPP__
