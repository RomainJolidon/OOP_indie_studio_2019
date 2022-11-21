/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_GRAPHIC_HPP
#define BOMBERMAN_GRAPHIC_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include "visual/VisualManager.hpp"
#include "scenes/SceneIndex.hpp"
#include "scenes/SceneGame.hpp"
#include "scenes/SceneOption.hpp"
#include "scenes/SceneMenu.hpp"
#include "scenes/SceneMapSelection.hpp"
#include "scenes/ScenePlayerSelection.hpp"
#include "config/Config.hpp"
#include "config/GameConfig.hpp"

class Game {
    public:
    Game(const std::string& title = "Bomberman - The indie game");
    Game(const Game& graphic) = default;
    Game &operator=(const Game& graphic) = default;
    void registerNewScene(SceneIndex sceneIndex, const std::shared_ptr<IScene>& scene);
    void setSceneIndex(SceneIndex sceneIndex);
    VisualManager &getVisualManager();
    Config &getConfig();
    GameConfig &getGameConfig();
    void run();
    ~Game();

    protected:
    private:
    bool setActiveScene();
    Config _config;
    GameConfig _gameConfig;
    VisualManager _visualManager;
    std::unordered_map<SceneIndex, std::shared_ptr<IScene>> _sceneMap;
    std::vector<SceneIndex> _sceneTree;
};

#endif //BOMBERMAN_GRAPHIC_HPP
