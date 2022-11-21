/*
** EPITECH PROJECT, 2020
** SceneOption
** File description:
** SceneOption
*/

#include "scenes/SceneOption.hpp"


SceneOption::SceneOption(VisualManager &visualManager, Config &config,
    GameConfig &gameConfig
) : AScene(visualManager, config, gameConfig)
{
    createAllEntities();
}

SceneOption::~SceneOption()
{}

void SceneOption::oneCycleLoop()
{
    std::string volume = std::to_string(_config.getVolume());
    reinterpret_cast<irr::gui::IGUIStaticText *>(_GUIEnv->getGUIElement(_textVolumeID))->setText(std::wstring(volume.begin(), volume.end()).c_str());
    display();
}

void SceneOption::createAllEntities()
{
    _textVolumeID = IdGen::getNewId();

    addButton({0, 0, 200, 200}, nullptr, "Go Back", [&](){
        _config.playSoundEffect(VALIDATE);
        _config.setSceneIndex(BACK_SCENE);
    });
    addButton({0, 210, 200, 410}, nullptr, "Menu", [&](){
        _config.playSoundEffect(VALIDATE);
        _config.setSceneIndex(MENU);
    });
    addButton({810, 400, 910, 500}, nullptr, "Vol. Down", [&](){
        _config.playSoundEffect(VALIDATE);
        _config.setVolume(_config.getVolume() - 10);
    });
    _GUIEnv->createText({910, 400, 1010, 500}, std::to_string(_config.getVolume()), false, _textVolumeID);
    reinterpret_cast<irr::gui::IGUIStaticText *>(_GUIEnv->getGUIElement(_textVolumeID))->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
    addButton({1010, 400, 1110, 500}, nullptr, "Vol. Up", [&](){
        _config.playSoundEffect(VALIDATE);
        _config.setVolume(_config.getVolume() + 10);
    });
}

void SceneOption::emptyAllEntities()
{
}

void SceneOption::resetGame()
{
}

void SceneOption::load()
{
    /*for (auto &node: _modelStorage.componentVector) {
        node.mesh->activate();
    }*/
    _camera->load();
    _visualManager.getDevice().setInputReceivingSceneManager(_sceneManager);
    _GUIEnv->load();
    _visualManager.getDevice().setEventReceiver(&_GUIEnv->getEventManager());
    _loaded = true;
}

void SceneOption::unload()
{
    _GUIEnv->unload();
    _camera->unload();
    _loaded = false;
}