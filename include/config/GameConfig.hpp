/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_GAMECONFIG_HPP
#define BOMBERMAN_GAMECONFIG_HPP

#include <irrlicht.h>
#include <vector>
#include <iostream>
#include <memory>
#include "config/JsonData.hpp"

enum PlayerType{AI = 0, PLAYER = 1};

class GameConfig {
    public:
    GameConfig() = default;
    ~GameConfig() = default;
    PlayerType &operator [](unsigned int value);
    void setKeybindsForPlayer(unsigned int playerValue, const std::vector<irr::EKEY_CODE> &keybinds);
    void setMap(const std::shared_ptr<JsonData> &map, const std::string &mapName);
    void setCharsTypes(const std::vector<PlayerType>& charsTypes);
    void setSeed(const unsigned int& seed);
    const std::shared_ptr<JsonData> & getMap() const;
    const std::string & getMapName() const;
    const std::vector<PlayerType>& getCharsTypes() const;
    const unsigned int& getSeed() const;
    void clearCharsTypes();
    void setPause(bool pause);
    bool getPause() const;

    protected:
    private:
    unsigned int _seed;
    PlayerType _playerType[4];
    irr::EKEY_CODE _keybinds[4][5];
    std::shared_ptr<JsonData> _map;
    std::vector<PlayerType> _charsTypes;
    std::string _mapName;
    bool _gamePaused;
};

#endif //BOMBERMAN_GAMECONFIG_HPP
