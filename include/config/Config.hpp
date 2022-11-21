/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_CONFIG_HPP
#define BOMBERMAN_CONFIG_HPP

#include <iostream>
#include "config/JsonParser.hpp"
#include "scenes/SceneIndex.hpp"

#include <SFML/Audio.hpp>

enum SoundEffect {
    VALIDATE,
    EXPLOSION
};

enum MapSize {
    SMALL,
    MEDIUM,
    LARGE
};

class Config {
    public:
    Config(const std::string &filepath);
    ~Config();
    int getVolume() const;
    int getWidth() const;
    int getHeight() const;
    void setSceneIndex(const SceneIndex &sceneIndex);
    void setVolume(int volume);
    void setMapSize(MapSize mapSize);
    MapSize getMapSize();
    void loadMusic(std::string filepath);
//    void loadSoundEffect(std::string filepath);
    void stopMusic();
    void playMusic();
    void playSoundEffect(SoundEffect sound);
    SceneIndex getSceneIndex() const;

    protected:
    private:
    void parseConfig();
    JsonData _configData;
    int _volume;
    int _width;
    int _height;
    sf::Music *_music;
    sf::Music *_explosion;
    sf::Music *_validate;
    SceneIndex _sceneIndex;
    MapSize _mapSize;
};

#endif //BOMBERMAN_CONFIG_HPP
