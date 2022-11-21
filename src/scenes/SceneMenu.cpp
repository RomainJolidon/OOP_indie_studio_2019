/*
** EPITECH PROJECT, 2020
** SceneMenu
** File description:
** SceneMenu
*/
#include "scenes/SceneMenu.hpp"

SceneMenu::SceneMenu(VisualManager &visualManager, Config &config,
    GameConfig &gameConfig
) : AScene(
    visualManager, config, gameConfig)
{
    _camera->setPosition(6, 0, 0);
    _camera->lookAt(0, 3, 0);
    createAllEntities();
}

SceneMenu::~SceneMenu()
{
    _dancer.first->remove();
    _dancer.second->remove();
}

void SceneMenu::oneCycleLoop()
{
    display();
}

void SceneMenu::load()
{
    /*for (auto &node: _modelStorage.componentVector) {
        node.mesh->activate();
    }*/
    _GUIEnv->load();
    _camera->load();
    _sceneManager->setActiveCamera(_camera->getCamera());
    _visualManager.getDevice().setInputReceivingSceneManager(_sceneManager);
    _visualManager.getDevice().setEventReceiver(&_GUIEnv->getEventManager());
    _dancer.first->setVisible(true);
    _dancer.second->setVisible(true);
    _loaded = true;
}

void SceneMenu::unload()
{
    _GUIEnv->unload();
    _camera->unload();
    _dancer.first->setVisible(false);
    _dancer.second->setVisible(false);
    /*for (auto &node: _modelStorage.componentVector) {
        node.mesh->desactivate();
    }*/
    //_driver->removeAllTextures();
    _loaded = false;
}

void SceneMenu::createAllEntities()
{
    addButton({860, 450, 1060, 650}, _driver->getTexture("../assets/bombButton.png"), "PLAY", [&](){
        _config.playSoundEffect(VALIDATE);
        _config.setSceneIndex(MAP_SELECTION);
    });
    addButton({740, 670, 940, 870}, _driver->getTexture("../assets/bombButton.png"), "OPTIONS", [&](){
        _config.playSoundEffect(VALIDATE);
        _config.setSceneIndex(OPTIONS);
    });
    addButton({980, 670, 1180, 870}, _driver->getTexture("../assets/bombButton.png"), "QUIT", [&](){
        _config.playSoundEffect(VALIDATE);
        _visualManager.getDevice().closeDevice();
    });

    _dancer.first = addAnimatedMesh("../assets/bomberguy/dance.b3d");
    _dancer.first->setPosition(irr::core::vector3df{0.f, 0.f, 3.f});
    _dancer.first->setScale(irr::core::vector3df{0.05f, 0.05f, 0.05f});
    _dancer.first->setRotation(irr::core::vector3df{0.f, -90.f, -20.f});
    _dancer.first->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _dancer.first->setMaterialTexture(0, _driver->getTexture("../assets/bomberguy/Texture.png"));

    _dancer.second = addAnimatedMesh("../assets/bomberguy/dance.b3d");
    _dancer.second->setPosition(irr::core::vector3df{0.f, 0.f, -3.f});
    _dancer.second->setScale(irr::core::vector3df{0.05f, 0.05f, 0.05f});
    _dancer.second->setRotation(irr::core::vector3df{0.f, -90.f, -20.f});
    _dancer.second->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _dancer.second->setMaterialTexture(0, _driver->getTexture("../assets/bomberguy/Texture.png"));

    addImage(irr::core::rect<int>(0, 0, 1920, 1080), "../assets/backgroundMenu.png");
    addImage(irr::core::rect<int>(500, 100, 1420, 400), "../assets/titleMenu.png");
}

void SceneMenu::emptyAllEntities()
{
}

void SceneMenu::resetScene()
{
}
