/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Sound
 *
 * File creation = 01/06/2020
 * Last modification = 01/06/2020
 */

#ifndef __BOMBERMAN_SOUND_HPP__
#define __BOMBERMAN_SOUND_HPP__

#include <SFML/Audio.hpp>
#include <iostream>

namespace indie::object {
    class Sound {
        public:
            Sound();
            Sound(const std::string &musicPath, unsigned int volume = 50);
            ~Sound();
            void setVolume(unsigned int volume);
            void play();
            void stop();
        private:
            bool _hasError;
            sf::SoundBuffer _soundBuffer;
            sf::Sound _sound;
    };
}

#endif //__BOMBERMAN_SOUND_HPP__
