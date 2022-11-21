/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include "Game.hpp"

Game::Game(const std::string &title):
_config("../config/mainConfig.json"), _visualManager(title, _config.getWidth(), _config.getHeight())
{
    _gameConfig.setSeed(0);
}

void Game::run()
{
    SceneIndex lastIdx = _config.getSceneIndex();

    for (auto &scene: _sceneMap) {
        if (scene.first != _config.getSceneIndex()) {
            scene.second->unload();
        }
    }
    while(_visualManager.isRunning())
    {
        if (lastIdx != _config.getSceneIndex()) {
            _sceneMap[lastIdx]->unload();
            setActiveScene();
            lastIdx = _config.getSceneIndex();
        }
        if (_config.getSceneIndex() != NONE_SCENE) {
            _sceneMap[_config.getSceneIndex()]->oneCycleLoop();
        } else
            std::cerr << "no scene selected" << std::endl;
    }
}

Game::~Game()
{
    _sceneMap.clear();
}

void Game::registerNewScene(SceneIndex sceneIndex, const std::shared_ptr<IScene>& scene)
{
    if (!_sceneMap.empty() && _sceneMap.find(sceneIndex) != _sceneMap.end()) {
        std::cerr << "scene with index " << sceneIndex << " already exists" << std::endl;
        return;
    }
    _sceneMap[sceneIndex] = scene;
}

void Game::setSceneIndex(SceneIndex sceneIndex)
{
    SceneIndex curSceneIndex = _config.getSceneIndex();

    if (curSceneIndex != NONE_SCENE && _sceneMap.find(curSceneIndex) != _sceneMap.end() && _sceneMap[curSceneIndex]->isSceneLoaded()) {
        _sceneMap[curSceneIndex]->unload();
    }
    _config.setSceneIndex(sceneIndex);
    setActiveScene();
}

VisualManager &Game::getVisualManager()
{
    return (_visualManager);
}

bool Game::setActiveScene()
{
    if (_config.getSceneIndex() != BACK_SCENE && (_config.getSceneIndex() == NONE_SCENE || _sceneMap.find(_config.getSceneIndex()) == _sceneMap.end())) {
        return (false);
    }
    if (_config.getSceneIndex() == BACK_SCENE) {
        _config.setSceneIndex(_sceneTree[_sceneTree.size() - 2]);
    }
    if (!_sceneMap[_config.getSceneIndex()]->isSceneLoaded()) {
        _sceneMap[_config.getSceneIndex()]->load();
        _sceneTree.push_back(_config.getSceneIndex());
    }
    return (true);
}

Config &Game::getConfig()
{
    return _config;
}

GameConfig &Game::getGameConfig()
{
    return _gameConfig;
}
