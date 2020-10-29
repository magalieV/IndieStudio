/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Music
 *
 * File creation = 01/06/2020
 * Last modification = 01/06/2020
 */

#ifndef __BOMBERMAN_MUSIC_HPP__
#define __BOMBERMAN_MUSIC_HPP__

#include <SFML/Audio.hpp>
#include <iostream>

namespace indie::object {
    class Music {
        public:
            Music();
            Music(const std::string &musicPath,
                unsigned int volume = 50,
                bool loop = true);
            ~Music();
            void setLoop(bool state);
            void setVolume(unsigned int volume);
            void play();
            void stop();
        private:
            bool _hasError;
            sf::Music _music;
    };
}

#endif //__BOMBERMAN_MUSIC_HPP__
