/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include "config/Config.hpp"

Config::Config(const std::string &filepath):
_configData(JsonParser::parseJson(filepath)), _sceneIndex(NONE_SCENE)
{
    _mapSize = SMALL;
    _volume = 50;
    _music = new sf::Music();
    _explosion = new sf::Music();
    _validate = new sf::Music();
    if (!_music->openFromFile("../assets/music/sans.wav")) {
        std::cerr << "error when loading" << std::endl;
        _music = nullptr;
    }
    if (!_explosion->openFromFile("../assets/music/Explosion+7.wav")) {
        std::cerr << "error when loading" << std::endl;
        _explosion = nullptr;
    }
    if (!_validate->openFromFile("../assets/music/validate.wav")) {
        std::cerr << "error when loading" << std::endl;
        _validate = nullptr;
    }
    _validate->setVolume(20);
    parseConfig();
}

Config::~Config()
{
    _music->stop();
    _explosion->stop();
    _validate->stop();
    delete _music;
    delete _explosion;
    delete _validate;
}

void Config::parseConfig()
{
    _volume = std::atoi(_configData.getAttributeOfKey("volume").c_str());
    _width = std::atoi(_configData.getAttributeOfKey("width").c_str());
    _height = std::atoi(_configData.getAttributeOfKey("height").c_str());
}

int Config::getVolume() const
{
    return _volume;
}

int Config::getWidth() const
{
    return _width;
}

int Config::getHeight() const
{
    return _height;
}

void Config::setSceneIndex(const SceneIndex &sceneIndex)
{
    _sceneIndex = sceneIndex;
}

SceneIndex Config::getSceneIndex() const
{
    return _sceneIndex;
}

void Config::setVolume(int volume)
{
    if (volume >= 0 && volume <= 100)
        _volume = volume;
    _music->setVolume(_volume);
}

void Config::loadMusic(std::string filepath)
{
    if (!_music->openFromFile(filepath)) {
        std::cerr << "error loading music" << std::endl;
        _music = nullptr;
    }
}

void Config::stopMusic()
{
    if (_music)
        _music->stop();
}

void Config::playMusic()
{
    if (_music) {
        _music->play();
        _music->setLoop(_music);
        _music->setVolume(_volume);
    }
}

//void Config::loadSoundEffect(std::string filepath)
//{
//    _explosion->openFromFile(filepath);
//}

void Config::playSoundEffect(SoundEffect sound)
{
    switch (sound) {
    case VALIDATE:
        if (_validate) {
            _validate->stop();
            _validate->play();
        }
        break;
    case EXPLOSION:
        if (_explosion) {
            _explosion->stop();
            _explosion->play();
        }
        break;
    }
}

void Config::setMapSize(MapSize mapSize)
{
    _mapSize = mapSize;
}

MapSize Config::getMapSize()
{
    return _mapSize;
}
