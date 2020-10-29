/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Sound
 *
 * File creation = 01/06/2020
 * Last modification = 01/06/2020
 */

#include "objects/Sound.hpp"

indie::object::Sound::Sound()
{
    _hasError = true;
}

indie::object::Sound::Sound(const std::string &musicPath, unsigned int volume)
{
    _soundBuffer = sf::SoundBuffer();
    if (!_soundBuffer.loadFromFile(musicPath)) {
        _hasError = true;
    } else {
        _sound.setBuffer(_soundBuffer);
        _sound.setVolume(volume);
        _hasError = false;
    }
}

indie::object::Sound::~Sound()
{
    if (!_hasError && _sound.getStatus() != sf::SoundSource::Status::Stopped)
        _sound.stop();
}

void indie::object::Sound::setVolume(unsigned int volume)
{
    if (!_hasError)
        _sound.setVolume(volume);
}

void indie::object::Sound::play()
{
    if (!_hasError && _sound.getStatus() != sf::Sound::Playing) {
        _sound.play();
    }
}

void indie::object::Sound::stop()
{
    if (!_hasError)
        _sound.stop();
}