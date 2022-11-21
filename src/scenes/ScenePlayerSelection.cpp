/*
** EPITECH PROJECT, 2023
** ScenePlayerSelection
** File description:
** Created by rjolidon,
*/

#include "scenes/ScenePlayerSelection.hpp"

ScenePlayerSelection::ScenePlayerSelection(VisualManager &visualManager, Config &config,
    GameConfig &gameConfig) : AScene(visualManager, config, gameConfig)
{
    _camera->setPosition(100, 0, 0);
    _camera->lookAt(0, 0, 0);
    createAllEntities();
}

ScenePlayerSelection::~ScenePlayerSelection()
{}

void ScenePlayerSelection::oneCycleLoop()
{
    display();
}

void ScenePlayerSelection::selectChar(PlayerType& charType, unsigned int buttonId, unsigned int textId, int pos)
{
    std::wstring wtxt;

    if (pos == 0) {
        wtxt = std::wstring(L"Arrow keys to move\nB to place bombs");
    } else if (pos == 1) {
        wtxt = std::wstring(L"ZQSD to move\nE to place bombs");
    } else if (pos == 2) {
        wtxt = std::wstring(L"TFGH to move\nY to place bombs");
    } else {
        wtxt = std::wstring(L"IJKL to move\nO to place bombs");
    }
    if (charType == PlayerType::AI) {
        irr::gui::IGUIButton *button = reinterpret_cast<irr::gui::IGUIButton*>(_GUIEnv->getGUIElement(buttonId));
        button->setText(L"REMOVE PLAYER");
        charType = PlayerType::PLAYER;
        irr::gui::IGUIStaticText *txt = reinterpret_cast<irr::gui::IGUIStaticText*>(_GUIEnv->getGUIElement(textId));
        txt->setText(wtxt.c_str());
    } else {
        irr::gui::IGUIButton *button = reinterpret_cast<irr::gui::IGUIButton*>(_GUIEnv->getGUIElement(buttonId));
        button->setText(L"ADD PLAYER");
        charType = PlayerType::AI;
        irr::gui::IGUIStaticText *txt = reinterpret_cast<irr::gui::IGUIStaticText*>(_GUIEnv->getGUIElement(textId));
        txt->setText(L"");
    }
    _gameConfig.setCharsTypes(charsTypes);
}

void ScenePlayerSelection::createAllEntities()
{
    charsTypes = std::vector<PlayerType>({ AI, AI, AI, AI });
    _buttonsIds = std::vector<int>({ IdGen::getNewId(), IdGen::getNewId(), IdGen::getNewId(), IdGen::getNewId() });
    _textsIds = std::vector<int>({ IdGen::getNewId(), IdGen::getNewId(), IdGen::getNewId(), IdGen::getNewId() });
    _gameConfig.setCharsTypes(charsTypes);

    _GUIEnv->createText({310, 330, 550, 430}, "", false, _textsIds[0]);
    _GUIEnv->createText({1210, 330, 1450, 430}, "", false, _textsIds[1]);
    _GUIEnv->createText({310, 830, 550, 1130}, "", false, _textsIds[2]);
    _GUIEnv->createText({1210, 830, 1450, 1130}, "", false, _textsIds[3]);

    _GUIEnv->createButton({300, 200, 500, 300}, nullptr, "ADD PLAYER", [&](){
        _config.playSoundEffect(VALIDATE);
        selectChar(charsTypes[0], _buttonsIds[0], _textsIds[0], 0);
    }, _buttonsIds[0]);
    _GUIEnv->createButton({1200, 200, 1400, 300}, nullptr, "ADD PLAYER", [&](){
        _config.playSoundEffect(VALIDATE);
        selectChar(charsTypes[1], _buttonsIds[1], _textsIds[1], 1);
    }, _buttonsIds[1]);
    _GUIEnv->createButton({300, 700, 500, 800}, nullptr, "ADD PLAYER", [&](){
        _config.playSoundEffect(VALIDATE);
        selectChar(charsTypes[2], _buttonsIds[2], _textsIds[2], 2);
    }, _buttonsIds[2]);
    _GUIEnv->createButton({1200, 700, 1400, 800}, nullptr, "ADD PLAYER", [&](){
        _config.playSoundEffect(VALIDATE);
        selectChar(charsTypes[3], _buttonsIds[3], _textsIds[3], 3);
    }, _buttonsIds[3]);
    addButton({1500, 700, 1700, 900}, nullptr, "PLAY", [&](){
        _config.playSoundEffect(VALIDATE);
        _config.setSceneIndex(GAME);
    });
    createModels();
}

void ScenePlayerSelection::emptyAllEntities()
{
    _modelStorage.componentVector.clear();
}

void ScenePlayerSelection::load()
{
    _gameConfig.clearCharsTypes();
    _gameConfig.setCharsTypes(std::vector<PlayerType>({ AI, AI, AI, AI }));
    if (charsTypes.size() == 0) {
        charsTypes = std::vector<PlayerType>({ AI, AI, AI, AI });
    }
    for (auto &node: _modelStorage.componentVector) {
        node.mesh->activate();
    }
    _camera->load();
    _sceneManager->setActiveCamera(_camera->getCamera());
    _visualManager.getDevice().setInputReceivingSceneManager(_sceneManager);
    _GUIEnv->load();
    _visualManager.getDevice().setEventReceiver(&_GUIEnv->getEventManager());
    _loaded = true;
}

void ScenePlayerSelection::createModels()
{
    unsigned long long _id;
    std::vector<ECSEntity> modelEntities;

    modelEntities = std::vector<ECSEntity>({ _instance.newEntity(), _instance.newEntity(), _instance.newEntity(), _instance.newEntity() });
    _id = modelEntities[0]._id;
    std::shared_ptr<IMesh> model1 =
        _visualManager.getNewAnimatedMesh(addAnimatedMesh(PLAYER1_IDLE),
        addAnimatedMesh(PLAYER1_RUNNING),
        _driver->getTexture(PLAYER1_TEXTURE),
        irr::core::vector3df(0, 40, -80),
        irr::core::vector3df(0, 250, 0));
    model1->setScale(70, 70, 70);
    _modelStorage.addComponentForEntity(_id);
    _modelStorage.getComponentForEntity(_id) =
        Model{_id, model1};
    _id = modelEntities[1]._id;
    std::shared_ptr<IMesh> model2 =
        _visualManager.getNewAnimatedMesh(addAnimatedMesh(PLAYER2_IDLE),
        addAnimatedMesh(PLAYER2_RUNNING),
        _driver->getTexture(PLAYER2_TEXTURE),
        irr::core::vector3df(0, 42, 50),
        irr::core::vector3df(0, 290, 0));
    model2->setScale(400, 400, 400);
    _modelStorage.addComponentForEntity(_id);
    _modelStorage.getComponentForEntity(_id) =
        Model{_id, model2};
    _id = modelEntities[2]._id;
    std::shared_ptr<IMesh> model3 =
        _visualManager.getNewAnimatedMesh(addAnimatedMesh(PLAYER3_IDLE),
        addAnimatedMesh(PLAYER3_RUNNING),
        _driver->getTexture(PLAYER3_TEXTURE),
        irr::core::vector3df(0, -30, -80),
        irr::core::vector3df(0, 230, 0));
    model3->setScale(20, 22, 20);
    _modelStorage.addComponentForEntity(_id);
    _modelStorage.getComponentForEntity(_id) =
        Model{_id, model3};
    _id = modelEntities[3]._id;
    std::shared_ptr<IMesh> model4 =
        _visualManager.getNewAnimatedMesh(addAnimatedMesh(PLAYER4_IDLE),
        addAnimatedMesh(PLAYER4_RUNNING),
        _driver->getTexture(PLAYER4_TEXTURE),
        irr::core::vector3df(0, -30, 50),
        irr::core::vector3df(0, 280, 0));
    model4->setScale(20, 20, 20);
    _modelStorage.addComponentForEntity(_id);
    _modelStorage.getComponentForEntity(_id) =
        Model{_id, model4};
}

void ScenePlayerSelection::unload()
{
    _GUIEnv->unload();
    _camera->unload();
    for (auto &node: _modelStorage.componentVector) {
        node.mesh->desactivate();
    }
    for (auto id : _buttonsIds) {
        irr::gui::IGUIButton *button = reinterpret_cast<irr::gui::IGUIButton*>(_GUIEnv->getGUIElement(id));
        button->setText(L"ADD PLAYER");
    }
    for (auto id : _textsIds) {
        irr::gui::IGUIStaticText *text = reinterpret_cast<irr::gui::IGUIStaticText*>(_GUIEnv->getGUIElement(id));
        text->setText(L"");
    }
    charsTypes.clear();
    _loaded = false;
}

void ScenePlayerSelection::resetScene()
{
    emptyAllEntities();
}