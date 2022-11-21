/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include "scenes/AScene.hpp"

AScene::AScene(VisualManager &visualManager, Config &config,
    GameConfig &gameConfig
) :
    _config(config), _eventManager(new EventManager), _visualManager(visualManager), _gameConfig(gameConfig),
_driver(nullptr), _sceneManager(nullptr), _GUIEnv(nullptr),
_camera(nullptr), _loaded(false), _initialized(false)
{
    _driver = _visualManager.getDevice().getVideoDriver();
    _sceneManager = _visualManager.getDevice().getSceneManager();
    //set camera
    _camera = std::unique_ptr<Camera>(new Camera(*_sceneManager));
    _GUIEnv = std::unique_ptr<IGUI>(new GUI(nullptr,
        std::reference_wrapper<irr::scene::ISceneManager>(*_sceneManager),
        std::reference_wrapper<IEventManager>(*_eventManager)
        ));
    if (!_GUIEnv) {
        std::cerr << "Failed to init GUI Env" << std::endl;
    } else {
        _GUIEnv->load();
        _visualManager.getDevice().setEventReceiver(&_GUIEnv->getEventManager());
    }
}

AScene::~AScene()
{

}

irr::scene::IMeshSceneNode *AScene::addMesh(const std::string &meshPath)
{
    irr::scene::IMeshSceneNode *node(_sceneManager->addMeshSceneNode(_sceneManager->getMesh(meshPath.c_str())));

    return (node);
}

irr::scene::IAnimatedMeshSceneNode *AScene::addAnimatedMesh(
    const std::string &meshPath
)
{
    irr::scene::IAnimatedMeshSceneNode *node(_sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh(meshPath.c_str())));

    return (node);
}

const irr::scene::ISceneManager& AScene::getScene() const
{
    return (*_sceneManager);
}

bool AScene::isSceneLoaded() const
{
    return _loaded;
}

void AScene::addButton(const irr::core::recti &rectInSpace, irr::video::ITexture *image,
                      const std::string &content, const ButtonInitializer& buttonFun
)
{

    if (_GUIEnv) {
        _GUIEnv->createButton(rectInSpace, image, content, buttonFun, IdGen::getNewId());
    } else {
        std::cerr << "GUI Env is not initialized" << std::endl;
    }
}

void AScene::addText(const irr::core::recti &rectInSpace,
    const std::string &content, bool bordered
)
{
    if (_GUIEnv) {
        _GUIEnv->createText(rectInSpace, content, bordered, IdGen::getNewId());
    } else {
        std::cerr << "GUI Env is not initialized" << std::endl;
    }
}

void AScene::addImage(const irr::core::recti &rectInSpace, const std::string &path)
{
    irr::video::ITexture *image = _driver->getTexture(path.c_str());

    _images.push_back(std::pair<irr::video::ITexture *, irr::core::recti>(image, rectInSpace));
}

void AScene::display() const
{
    _driver->beginScene(true, true, irr::video::SColor(255,100,101,140)); // debut de l'affichage
    
    irr::video::ITexture *image = _driver->getTexture("../assets/background.jpg");
    _driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_16_BIT, true);
    _driver->draw2DImage(image, irr::core::vector2d<int>(0, 0),
        irr::core::rect<int>(0, 0, 1920, 1080), 0,
        irr::video::SColor(255, 255, 255, 255), true);
    for (auto &it: _images) {
        _driver->draw2DImage(it.first, it.second,
            irr::core::rect<int>(0, 0, it.first->getSize().Width, it.first->getSize().Height), 0, 0, true);
    }
    _sceneManager->drawAll();
    if (_GUIEnv)
        _GUIEnv->display();
    _driver->endScene();
}

VisualManager &AScene::getVisualManager() const
{
    return _visualManager;
}

irr::scene::ISceneManager &AScene::getSceneManager() const
{
    return *_sceneManager;
}

irr::video::IVideoDriver &AScene::getVideoDriver() const
{
    return *_driver;
}
