/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include "config/GameConfig.hpp"



PlayerType &GameConfig::operator[](unsigned int value)
{
    if (value > 3)
        return (_playerType[value % 4]);
    return (_playerType[value]);
}

void GameConfig::setKeybindsForPlayer(unsigned int playerValue,
    const std::vector<irr::EKEY_CODE> &keybinds
)
{
    if (playerValue > 3)
        return;
    for (int i = 0; i < 5; i++) {
        _keybinds[playerValue][i] = keybinds[i];
    }
}

void GameConfig::setMap(const std::shared_ptr<JsonData> &map,
    const std::string &mapName
)
{
    _map = std::shared_ptr <JsonData>(map);
    _mapName = mapName;
}

void GameConfig::setCharsTypes(const std::vector<PlayerType>& charsTypes)
{
    _charsTypes = charsTypes;
}

void GameConfig::setSeed(const unsigned int& seed)
{
    _seed = seed;
}

const std::shared_ptr<JsonData> & GameConfig::getMap() const
{
    return (_map);
}

const std::string &GameConfig::getMapName() const
{
    return _mapName;
}

const std::vector<PlayerType>& GameConfig::getCharsTypes() const
{
    return (_charsTypes);
}

const unsigned int& GameConfig::getSeed() const
{
    return (_seed);
}

void GameConfig::clearCharsTypes()
{
    _charsTypes.clear();
}

void GameConfig::setPause(bool pause)
{
    _gamePaused = pause;
}

bool GameConfig::getPause() const
{
    return _gamePaused;
}
