/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Music
 *
 * File creation = 01/06/2020
 * Last modification = 01/06/2020
 */

#include "objects/Music.hpp"

indie::object::Music::Music()
{
    _hasError = true;
}

indie::object::Music::Music(const std::string &musicPath, unsigned int volume,
    bool loop)
{
    if (!_music.openFromFile(musicPath))
        _hasError = true;
    else {
        _music.setLoop(loop);
        _music.setVolume(volume);
        _hasError = false;
    }
}

indie::object::Music::~Music()
{
    if (!_hasError && _music.getStatus() != sf::SoundSource::Status::Stopped)
        _music.stop();
}

void indie::object::Music::setLoop(bool state)
{
    if (!_hasError)
        _music.setLoop(state);
}

void indie::object::Music::setVolume(unsigned int volume)
{
    if (!_hasError)
        _music.setVolume(volume);
}

void indie::object::Music::play()
{
    if (!_hasError)
        _music.play();
}

void indie::object::Music::stop()
{
    if (!_hasError)
        _music.stop();
}