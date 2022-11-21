/*
** EPITECH PROJECT, 2020
** SceneGame
** File description:
** SceneGame
*/

#include <algorithm>
#include "scenes/SceneGame.hpp"
#include <cstdlib>
#include "config/JsonParser.hpp"

SceneGame::SceneGame(VisualManager &visualManager, Config &config,
    GameConfig &gameConfig
) : AScene(
    visualManager, config, gameConfig), _isGameEnded(false)
{
    _camera->setPosition(700, 150, -800);
    _camera->lookAt(700, 400, 0);
    createAllEntities();
}

SceneGame::~SceneGame()
{
    saveMap("../saves/maps.json");
}

void SceneGame::displayScore()
{
    Playable playable;
    std::wstring wtxt;
    std::string stxt;
    int i = 0;
    int speed;

    for (auto it : _playableStorage.entityIdxToComponentIdxMap) {
        playable = _playableStorage.getComponentForEntity(it.first);
        speed = static_cast<int>(_velocityStorage.getComponentForEntity(it.first).speedX);
        if (speed < 0)
            speed = -speed;
        stxt = std::string("Player " + std::to_string(playable.playerId) + std::string("\nNb bombs: ") + std::to_string(playable.stats.nbBombs)
            + "\nRange: " + std::to_string(playable.stats.range) + "\n"
            + "Speed: " + std::to_string(speed) + "\n");
        if (playable.stats.wallPass) {
            stxt = std::string(stxt + "Wall pass: true\n");
        } else {
            stxt = std::string(stxt + "Wall pass: false\n");
        }
        wtxt = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(stxt);
        irr::gui::IGUIButton *button = reinterpret_cast<irr::gui::IGUIButton*>(_GUIEnv->getGUIElement(_scoresIds[_playableStorage.getComponentForEntity(it.first).playerId-1]));
        button->setText(wtxt.c_str());
        i++;
    }
}

void SceneGame::oneCycleLoop()
{
    _elapsedTime = static_cast<unsigned long long int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _clock).count());
    displayScore();
    _mapSystem.update(_map, _positionStorage, _colliderStorage,
        _destroyableStorage, _playableStorage, _explosiveStorage);
    _inputSystem.update(_playableStorage, _velocityStorage, _positionStorage,
        _eventManager, _orientationStorage);
    _actionSystem.update(_positionStorage, _velocityStorage, _playableStorage,
        _orientationStorage, _instance, _colliderStorage, _explosiveStorage,
        _modelStorage, std::reference_wrapper<IScene>(*this), _map);
    _explosiveSystem.update(_explosiveStorage, _colliderStorage, _modelStorage,
        _positionStorage, _elapsedTime, std::reference_wrapper<IScene>(*this),
        _map, _destroyableStorage, _timerStorage, _instance);
    _timerSystem.update(_timerStorage, _destroyableStorage, _positionStorage,
        _modelStorage, _colliderStorage, _elapsedTime, _map, _destroyerStorage);
    _collisionSystem.update(_positionStorage, _velocityStorage,
        _colliderStorage, _collectibleStorage, _playableStorage, _modelStorage,
        _destroyableStorage, _destroyerStorage);
    if (_endgameSystem.update(_positionStorage, _velocityStorage, _playableStorage,
        _clockStorage, _colliderStorage, _orientationStorage, _modelStorage, _map)) {
        if (!_isGameEnded) {
            if (_playableStorage.componentVector.empty()) {
                addText({960, 130, 1060, 160}, "DRAW GAME !", false);
            } else  {
                addText({860, 130, 1060, 160},
                    "PLAYER " +
                std::to_string(_playableStorage.getComponentForEntity(_playableStorage.entityIdxToComponentIdxMap[0]).playerId)
                + " WON !", false);
            }
            addButton({860, 200, 1060, 400}, nullptr, "RETRY", [&]() {
                _map.clear();
                _config.playSoundEffect(VALIDATE);
                _GUIEnv->clearGui();
                resetGame();
                load();
            });
            addButton({860, 410, 1060, 610}, nullptr, "MAIN MENU", [&]() {
                _config.playSoundEffect(VALIDATE);
                _GUIEnv->clearGui();
                emptyAllEntities();
                createAllEntities();
                _config.setSceneIndex(MENU);
            });
            addButton({860, 620, 1060, 820}, nullptr, "QUIT", [&]() {
                _config.playSoundEffect(VALIDATE);
                _GUIEnv->clearGui();
                emptyAllEntities();
                _visualManager.getDevice().closeDevice();
            });
            _isGameEnded = true;
        }
    }
    _collectibleSystem.update(_positionStorage, _velocityStorage,
        _collectibleStorage, _playableStorage, _modelStorage,
        _destroyableStorage, _destroyerStorage);
    _effectSystem.update(_positionStorage, _velocityStorage, _playableStorage, _clockStorage, _instance, _colliderStorage, _explosiveStorage, _modelStorage, _map);
    _movementSystem.update(_positionStorage, _velocityStorage, _modelStorage,
        _orientationStorage, _clockStorage, _elapsedTime);
    _iaSystem.update(_velocityStorage, _colliderStorage, _positionStorage,
        _destroyableStorage, _playableStorage, _orientationStorage,
        _explosiveStorage, _map, _destroyerStorage);
    /*
    if (_eventManager->isKeyPressed(irr::KEY_ESCAPE)) {
        _config.playSoundEffect(VALIDATE);
        _config.setSceneIndex(OPTIONS);
        saveMap("../saves/maps.json");
    }
    */
    display();
}

bool SceneGame::CheckIfSpawn(int x, int y, int size, int length)
{
    if (y == 100 || y == (size-2)*100) {
        if (x != 100 && x != 200 && x != (length-3)*100 && x != (length-2)*100) {
            return (false);
        }
        return (true);
    }
    if (y == 200 || y == (size-3)*100) {
        if (x != 100 && x != (length-2)*100) {
            return (false);
        }
        return (true);
    }
    return (false);
}

bool SceneGame::CheckIfBorder(int x, int y, int size, int length)
{
    if (x == 300 || x == (length-4)*100) {
        if (y != 100 && y != (size-2)*100) {
            return (false);
        }
        return (true);
    }
    if (y == 300 || y == (size-4)*100) {
        if (x != 100 && x != (length-2)*100) {
            return (false);
        }
        return (true);
    }
    return (false);
}

void SceneGame::CreateBlock(int x, int y, const char *texturePath, bool destroyable)
{
    unsigned long long int actualId = _instance.newEntity()._id;

    _modelStorage.addComponentForEntity(actualId);
    _modelStorage.getComponentForEntity(actualId) =
        Model{
            actualId, _visualManager.getNewMesh(
                _sceneManager->addCubeSceneNode(100, 0, 1,
                    irr::core::vector3df(0, 0, 0),
                    irr::core::vector3df(0, 0, 0),
                    irr::core::vector3df(1, 1, 1)),
                _driver->getTexture(texturePath), irr::core::vector3df(x, y, 0),
                irr::core::vector3df(0, 0, 0))};
    _positionStorage.addComponentForEntity(actualId);
    _positionStorage.getComponentForEntity(actualId) = Position{actualId, (x/100), (y/100), static_cast<float>(x), static_cast<float>(y)};
    _colliderStorage.addComponentForEntity(actualId);
    _colliderStorage.getComponentForEntity(actualId) = Collider{actualId, 1, 1};

    if (destroyable) {
        _destroyableStorage.addComponentForEntity(actualId);
        _destroyableStorage.getComponentForEntity(actualId) = Destroyable{actualId, true};
    }
    _map[y / 100][x / 100] = destroyable ? 'x' : '*';
}

void SceneGame::CreateBonus(int x, int y, Effect effect)
{
    std::string asset;
    unsigned long long int id = _instance.newEntity()._id;

    switch (effect) {
    case SPEED_UP:
        asset = "../assets/bonus/Skate.png";
        break;
    case FIRE_UP:
        asset = "../assets/bonus/Fire.png";
        break;
    case WALL_PASS:
        asset = "../assets/bonus/Soft_Block_Pass.png";
        break;
    case BOMB_UP:
        asset = "../assets/bonus/Bombupixel.png";
        break;
    case NO_EFFECT:
        return;
    }
    _modelStorage.addComponentForEntity(id);
    _modelStorage.getComponentForEntity(id) =

        _modelStorage.getComponentForEntity(id) =
            Model{
                id, _visualManager.getNewMesh(
                    _sceneManager->addCubeSceneNode(50, 0, 1,
                        irr::core::vector3df(0, 0, 0),
                        irr::core::vector3df(0, 0, 0),
                        irr::core::vector3df(1, 1, 1)),
                    _driver->getTexture(asset.c_str()), irr::core::vector3df(x * 100, y * 100, 0),
                    irr::core::vector3df(0, 0, 0))};
    _positionStorage.addComponentForEntity(id);
    _positionStorage.getComponentForEntity(id) = Position{id, x, y, static_cast<float>(x * 100), static_cast<float>(y * 100)};
    _collectibleStorage.addComponentForEntity(id);
    _collectibleStorage.getComponentForEntity(id) = Collectible{id, effect};
}

void SceneGame::CreateCharacter(unsigned long long id, int pos, float posX,
    float posY, int speed
)
{
    _modelStorage.addComponentForEntity(id);
    _velocityStorage.addComponentForEntity(id);
    _positionStorage.addComponentForEntity(id);
    _colliderStorage.addComponentForEntity(id);
    _orientationStorage.addComponentForEntity(id);
    _clockStorage.addComponentForEntity(id);

    if (pos == 0) {
        _modelStorage.getComponentForEntity(id) =
        Model{
            id, _visualManager.getNewAnimatedMesh(
                addAnimatedMesh(PLAYER1_IDLE),
                addAnimatedMesh(PLAYER1_RUNNING),
                _driver->getTexture(PLAYER1_TEXTURE),
                irr::core::vector3df(posX, posY, 0),
                irr::core::vector3df(-90, 0, 0))};
        _modelStorage.getComponentForEntity(id).mesh->setScale(200, 200, 200);
    } else if (pos == 1) {
        _modelStorage.getComponentForEntity(id) =
        Model{
            id, _visualManager.getNewAnimatedMesh(
                addAnimatedMesh(PLAYER2_IDLE),
                addAnimatedMesh(PLAYER2_RUNNING),
                _driver->getTexture(PLAYER2_TEXTURE),
                irr::core::vector3df(posX, posY, 0),
                irr::core::vector3df(-90, 0, 0))};
        _modelStorage.getComponentForEntity(id).mesh->setScale(2000, 2000, 2000);
    } else if (pos == 2) {
        _modelStorage.getComponentForEntity(id) =
        Model{
            id, _visualManager.getNewAnimatedMesh(
                addAnimatedMesh(PLAYER3_IDLE),
                addAnimatedMesh(PLAYER3_RUNNING),
                _driver->getTexture(PLAYER3_TEXTURE),
                irr::core::vector3df(posX, posY, 0),
                irr::core::vector3df(-90, 0, 0))};
        _modelStorage.getComponentForEntity(id).mesh->setScale(70, 70, 70);
    } else {
        _modelStorage.getComponentForEntity(id) =
        Model{
            id, _visualManager.getNewAnimatedMesh(
                addAnimatedMesh(PLAYER4_IDLE),
                addAnimatedMesh(PLAYER4_RUNNING),
                _driver->getTexture(PLAYER4_TEXTURE),
                irr::core::vector3df(posX, posY, 0),
                irr::core::vector3df(-90, 0, 0))};
        _modelStorage.getComponentForEntity(id).mesh->setScale(60, 60, 60);
    }
    _velocityStorage.getComponentForEntity(id) = Velocity{id, posX, posY, static_cast<float>(speed), static_cast<float>(speed)};
    _positionStorage.getComponentForEntity(id) = Position{id, static_cast<int>(posX - 10)/100, static_cast<int>(posY - 10)/100, posX, posY};
    _colliderStorage.getComponentForEntity(id) = Collider{id, 1, 1};
    _orientationStorage.getComponentForEntity(id) = Orientation{id, 90};
    _clockStorage.getComponentForEntity(id) = Clock{id, 0, 20};
}

void SceneGame::createAllEntities()
{
    unsigned int randSeed = 0;
    _scoresIds = std::vector<int>({ IdGen::getNewId(), IdGen::getNewId(), IdGen::getNewId(), IdGen::getNewId() });
    _clock = std::chrono::steady_clock::now();

    randSeed = _gameConfig.getSeed();
    if (randSeed != 0) {
        std::srand(randSeed);
    } else {
        randSeed = std::time(nullptr);
        std::srand(randSeed);
        _gameConfig.setSeed(randSeed);
    }

    addButton({0, 0, 200, 100}, nullptr, "PAUSE", [&](){
        _config.playSoundEffect(VALIDATE);
        _config.setSceneIndex(OPTIONS);
        saveMap("../saves/maps.json");
    });
    _GUIEnv->createText({ 50, 200, 350, 300}, "Score 1", false, _scoresIds[0]);
    _GUIEnv->createText({ 1720, 200, 2020, 300}, "Score 2", false, _scoresIds[1]);
    _GUIEnv->createText({ 50, 900, 350, 1000}, "Score 3", false, _scoresIds[2]);
    _GUIEnv->createText({ 1720, 900, 2020, 1000}, "Score 4", false, _scoresIds[3]);
}

void SceneGame::emptyAllEntities()
{
    _instance._entityList.clear();
    _modelStorage.componentVector.clear();
    _modelStorage.entityIdxToComponentIdxMap.clear();
    _velocityStorage.componentVector.clear();
    _velocityStorage.entityIdxToComponentIdxMap.clear();
    _positionStorage.componentVector.clear();
    _positionStorage.entityIdxToComponentIdxMap.clear();
    _colliderStorage.componentVector.clear();
    _colliderStorage.entityIdxToComponentIdxMap.clear();
    _playableStorage.componentVector.clear();
    _playableStorage.entityIdxToComponentIdxMap.clear();
    _orientationStorage.componentVector.clear();
    _orientationStorage.entityIdxToComponentIdxMap.clear();
    _explosiveStorage.componentVector.clear();
    _explosiveStorage.entityIdxToComponentIdxMap.clear();
    _destroyableStorage.componentVector.clear();
    _destroyableStorage.entityIdxToComponentIdxMap.clear();
    _collectibleStorage.componentVector.clear();
    _collectibleStorage.entityIdxToComponentIdxMap.clear();
    _destroyerStorage.componentVector.clear();
    _destroyerStorage.entityIdxToComponentIdxMap.clear();
    _timerStorage.componentVector.clear();
    _timerStorage.entityIdxToComponentIdxMap.clear();
    _clockStorage.componentVector.clear();
    _clockStorage.entityIdxToComponentIdxMap.clear();
    charsTypes.clear();
}

void SceneGame::resetGame()
{
    emptyAllEntities();
    createAllEntities();
}

void SceneGame::load()
{
    _config.loadMusic("../assets/music/thundersnail.wav");
    _config.playMusic();
    for (auto &node: _modelStorage.componentVector) {
        node.mesh->activate();
    }
    initMapSize(false);
    if (_modelStorage.componentVector.empty() || _gameConfig.getMapName() != _mapName) {
        emptyAllEntities();
        loadMap();
    }
    _camera->load();
    _sceneManager->setActiveCamera(_camera->getCamera());
    _visualManager.getDevice().setInputReceivingSceneManager(_sceneManager);
    _GUIEnv->load();
    _visualManager.getDevice().setEventReceiver(&_GUIEnv->getEventManager());
    _loaded = true;
}

void SceneGame::unload()
{
    _GUIEnv->unload();
    _camera->unload();
    for (auto &node: _modelStorage.componentVector) {
        node.mesh->desactivate();
    }
    _gameConfig.clearCharsTypes();
    _config.loadMusic("../assets/music/sans.wav");
    _config.playMusic();
    _loaded = false;
}

void SceneGame::saveMap(const std::string &filepath)
{
    if (_map.empty() || _mapName.empty())
        return;

    JsonData save = JsonParser::parseJson(filepath);
    JsonData players(JsonData::getNewData(TAB, "players", init_list()), "", false);
    JsonData walls(JsonData::getNewData(TAB, "walls", init_list()), "", false);
    JsonData bonus(JsonData::getNewData(TAB, "bonus", init_list()), "", false);
    JsonData bombs(JsonData::getNewData(TAB, "bombs", init_list()), "", false);
    JsonData savedMap(JsonData::getNewData(OBJECT, "", init_list()), "", false);
    float speed = 0;

    //saving players stats
    for (auto &player: _playableStorage.componentVector) {
        speed = _velocityStorage.getComponentForEntity(player.entityId).speedX < 0 ?
            -_velocityStorage.getComponentForEntity(player.entityId).speedX : _velocityStorage.getComponentForEntity(player.entityId).speedX;
        players.addObject("", 7,
            JsonData::getNewData(STRING, "id", std::to_string(player.playerId)),
            JsonData::getNewData(STRING, "x", std::to_string(_positionStorage.getComponentForEntity(player.entityId).x)),
            JsonData::getNewData(STRING, "y", std::to_string(_positionStorage.getComponentForEntity(player.entityId).y)),
            JsonData::getNewData(STRING, "bombs", std::to_string(player.stats.nbBombs)),
            JsonData::getNewData(STRING, "range", std::to_string(player.stats.range)),
            JsonData::getNewData(STRING, "wallPass", std::to_string(player.stats.wallPass)),
            JsonData::getNewData(STRING, "speed", std::to_string(static_cast<int>(speed)))
            );
    }

    //saving walls stats
    for (auto &wall: _colliderStorage.componentVector) {
        if (_playableStorage.hasEntityComponent(wall.entityId) || _explosiveStorage.hasEntityComponent(wall.entityId))
            continue;
        walls.addObject("", 3,
            JsonData::getNewData(STRING, "x", std::to_string(_positionStorage.getComponentForEntity(wall.entityId).x)),
            JsonData::getNewData(STRING, "y", std::to_string(_positionStorage.getComponentForEntity(wall.entityId).y)),
            JsonData::getNewData(STRING, "destroyable", std::to_string(_destroyableStorage.hasEntityComponent(wall.entityId)))
            );
    }

    //saving bonus stats
    for (auto &it: _collectibleStorage.componentVector) {
        bonus.addObject("", 3,
            JsonData::getNewData(STRING, "x", std::to_string(_positionStorage.getComponentForEntity(it.entityId).x)),
            JsonData::getNewData(STRING, "y", std::to_string(_positionStorage.getComponentForEntity(it.entityId).y)),
            JsonData::getNewData(STRING, "type", std::to_string(it.effect))
        );
    }

    //saving placed bomb stats
    for (auto &bomb: _explosiveStorage.componentVector) {
        bombs.addObject("", 3,
            JsonData::getNewData(STRING, "x", std::to_string(_positionStorage.getComponentForEntity(bomb.entityId).x)),
            JsonData::getNewData(STRING, "y", std::to_string(_positionStorage.getComponentForEntity(bomb.entityId).y)),
            JsonData::getNewData(STRING, "range", std::to_string(bomb.range))
        );
    }

    if (save.getObjectWithAttribute("name", _mapName) != nullptr) {
        save.removeObjectWithAttribute("name", _mapName);
    }

    savedMap.addString("name", _mapName);
    savedMap.addString("size", std::to_string(_config.getMapSize()));
    savedMap.addString("seed", std::to_string(_gameConfig.getSeed()));

    savedMap << players << walls << bombs<< bonus;
    save << savedMap;

    save.writeData();
    _map.clear();
}

void SceneGame::loadMap()
{
    std::shared_ptr<JsonData> map;
    data_t *data;

    if (_gameConfig.getMapName().empty() || _gameConfig.getMap() == nullptr) {
        generateNewMap();
        return;
    }
    map = _gameConfig.getMap();
    if (map->getListOfKey("players") == nullptr) {
        std::cerr << "could not initialize players from save" << std::endl;
        return;
    }
    if (map->getListOfKey("walls") == nullptr) {
        std::cerr << "could not initialize walls from save" << std::endl;
        return;
    }
    if (map->getListOfKey("bombs") == nullptr) {
        std::cerr << "could not initialize bombs from save" << std::endl;
        return;
    }
    if (map->getListOfKey("bonus") == nullptr) {
        std::cerr << "could not initialize bonus from save" << std::endl;
        return;
    }

    _config.setMapSize(
        static_cast<MapSize>(std::atoi(map->getAttributeOfKey("size").c_str())));
    initMapSize();

    if (_gameConfig.getCharsTypes().empty()) {
        _gameConfig.setCharsTypes(std::vector<PlayerType>({AI, AI, AI, AI}));
    }
    //loading players
    for (int i = 0; i < static_cast<list_t *>(map->getListOfKey("players")->value)->size; i++) {
        data = static_cast<data_t *>(get_data_at_pos(
            static_cast<list_t *>(map->getListOfKey("players")->value), i));
        createCustomCharacter(std::atoi(get_attribute_of_key(data, "id")) - 1,
            std::atoi(get_attribute_of_key(data, "x")) * 100 + 10,
            std::atoi(get_attribute_of_key(data, "y")) * 100 + 10,
            !_gameConfig.getCharsTypes()[
                std::atoi(get_attribute_of_key(data, "id")) - 1],
            std::atoi(get_attribute_of_key(data, "bombs")),
            std::atoi(get_attribute_of_key(data, "range")),
            std::atoi(get_attribute_of_key(data, "wallPass")),
            std::atoi(get_attribute_of_key(data, "speed")));
    }

    //loading walls
    for (int i = 0; i < static_cast<list_t *>(map->getListOfKey("walls")->value)->size; i++) {
        data = static_cast<data_t *>(get_data_at_pos(
            static_cast<list_t *>(map->getListOfKey("walls")->value), i));
        CreateBlock(
            std::atoi(get_attribute_of_key(data, "x")) * 100,
            std::atoi(get_attribute_of_key(data, "y")) * 100,
            std::atoi(get_attribute_of_key(data, "destroyable")) == 0 ? "../assets/blocks/Brick.jpeg" : "../assets/blocks/Wood.png",
            std::atoi(get_attribute_of_key(data, "destroyable")));
    }
    //loading bombs
    for (int i = 0; i < static_cast<list_t *>(map->getListOfKey("bombs")->value)->size; i++) {
        data = static_cast<data_t *>(get_data_at_pos(
            static_cast<list_t *>(map->getListOfKey("bombs")->value), i));
        createBomb(
            std::atoi(get_attribute_of_key(data, "x")) * 100,
            std::atoi(get_attribute_of_key(data, "y")) * 100,
            0,
            std::atoi(get_attribute_of_key(data, "range"))
            );
    }
    //loading bonus
    for (int i = 0; i < static_cast<list_t *>(map->getListOfKey("bonus")->value)->size; i++) {
        data = static_cast<data_t *>(get_data_at_pos(
            static_cast<list_t *>(map->getListOfKey("bonus")->value), i));
        CreateBonus(
            std::atoi(get_attribute_of_key(data, "x")) * 100,
            std::atoi(get_attribute_of_key(data, "y")) * 100,
            static_cast<Effect>(std::atoi(get_attribute_of_key(data, "type")))
        );
    }
    _isGameEnded = false;
}

void SceneGame::createBomb(int x, int y, unsigned long long int parentId,
    int range
)
{
    unsigned long long int actualId = _instance.newEntity()._id;

    _explosiveStorage.addComponentForEntity(actualId);
    _colliderStorage.addComponentForEntity(actualId);
    _modelStorage.addComponentForEntity(actualId);
    _positionStorage.addComponentForEntity(actualId);
    _explosiveStorage.getComponentForEntity(actualId) = Explosive{actualId, parentId, range, {actualId, 0, 3}};
    _colliderStorage.getComponentForEntity(actualId) = Collider{actualId, 1, 1};
    _modelStorage.getComponentForEntity(actualId) = Model{actualId,
        _visualManager.getNewMesh(
            addMesh("../assets/bomb/Bomb.obj"),
            _driver->getTexture("../assets/bomb/Bomb.png"),
            irr::core::vector3df(x - 10, y - 10, 0),
            irr::core::vector3df(-90, 0, 0))};
    _positionStorage.getComponentForEntity(actualId) = Position{
        actualId, x / 100, y / 100, static_cast<float>(x), static_cast<float>(y)};
    _map[y / 100][x / 100] = 'b';
    _modelStorage.getComponentForEntity(actualId).mesh->getNode()->setScale({5, 5, 5});
}

void SceneGame::CreateFire(int x, int y)
{
    irr::scene::IParticleSystemSceneNode *particle = _sceneManager->addParticleSystemSceneNode();
    particle->setMaterialTexture(0, _driver->getTexture("../assets/particles/fire.bmp"));
    particle->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    particle->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    particle->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    particle->setPosition(irr::core::vector3df((x * 100), (y * 100), 0));

    irr::scene::IParticleEmitter *emitter = particle->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(-1.2, 0, -1.2, 1.2, 1.2, 1.2),
        irr::core::vector3df(0.0f, 0.0f, -0.03f),
        40,80, irr::video::SColor(0,255,255,255),
        irr::video::SColor(0,255,255,255), 1000,2000, 0,
        irr::core::dimension2d<irr::f32>(50.f, 50.f), irr::core::dimension2d<irr::f32>(100.f, 100.f));
    particle->setEmitter(emitter);
    emitter->drop();

    irr::scene::IParticleAffector* fade = particle->createFadeOutParticleAffector(
        irr::video::SColor(0,0,0,0), 1200);
    particle->addAffector(fade);
    fade->drop();

    unsigned long long int actualId = _instance.newEntity()._id;

    _positionStorage.addComponentForEntity(actualId);
    _modelStorage.addComponentForEntity(actualId);
    _timerStorage.addComponentForEntity(actualId);
    _destroyerStorage.addComponentForEntity(actualId);

    _positionStorage.getComponentForEntity(actualId) = Position{actualId, x, y, static_cast<float>(x * 100), static_cast<float>(y * 100)};
    _modelStorage.getComponentForEntity(actualId) = Model{actualId, std::shared_ptr<IMesh>(new Particle(particle))};
    _map[y][x] = 'f';
    _timerStorage.getComponentForEntity(actualId) = Timer{actualId, 0, 1};
    _destroyerStorage.getComponentForEntity(actualId).destroyer = true;
}

void SceneGame::createCustomCharacter(int characterId, float posX, float posY,
    bool isAi, int bombs, int range, bool wallPass, int speed
)
{
    unsigned long long int actualId = _instance.newEntity()._id;

    _playableStorage.addComponentForEntity(actualId);
    if (characterId == 0) {
        CreateCharacter(actualId, characterId, posX, posY, speed);
        _playableStorage.getComponentForEntity(actualId) = Playable{actualId, PLAYER_ONE, NO_ACTION, irr::EKEY_CODE::KEY_UP,
            irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT, irr::EKEY_CODE::KEY_KEY_B,
            NO_EFFECT, {bombs, range, wallPass}, true, isAi, {0, 0, 0}};
    } else if (characterId == 1) {
        CreateCharacter(actualId, characterId, posX, posY, speed);
        _playableStorage.getComponentForEntity(actualId) = Playable{actualId, PLAYER_TWO, NO_ACTION, irr::EKEY_CODE::KEY_KEY_Z,
            irr::EKEY_CODE::KEY_KEY_S, irr::EKEY_CODE::KEY_KEY_Q, irr::EKEY_CODE::KEY_KEY_D, irr::EKEY_CODE::KEY_KEY_E,
            NO_EFFECT, {bombs, range, wallPass}, true, isAi, {0, 0, 0}};
    } else if (characterId == 2) {
        CreateCharacter(actualId, characterId, posX, posY, speed);
        _playableStorage.getComponentForEntity(actualId) = Playable{actualId, PLAYER_THREE, NO_ACTION, irr::EKEY_CODE::KEY_KEY_T,
            irr::EKEY_CODE::KEY_KEY_G, irr::EKEY_CODE::KEY_KEY_F, irr::EKEY_CODE::KEY_KEY_H, irr::EKEY_CODE::KEY_KEY_Y,
            NO_EFFECT, {bombs, range, wallPass}, true, isAi, {0, 0, 0}};
    } else if (characterId == 3) {
        CreateCharacter(actualId, characterId, posX, posY, speed);
        _playableStorage.getComponentForEntity(actualId) = Playable{actualId, PLAYER_FOUR, NO_ACTION, irr::EKEY_CODE::KEY_KEY_I,
            irr::EKEY_CODE::KEY_KEY_K, irr::EKEY_CODE::KEY_KEY_J, irr::EKEY_CODE::KEY_KEY_L, irr::EKEY_CODE::KEY_KEY_O,
            NO_EFFECT, {bombs, range, wallPass}, true, isAi, {0, 0, 0}};
    }
}

void SceneGame::generateNewMap()
{
    int x = 0;
    int y = 0;
    int randNb = 0;
    float posX = 110;
    float posY;
    std::vector<ECSEntity> entities;

    entities.push_back(_instance.newEntity());
    entities.push_back(_instance.newEntity());
    entities.push_back(_instance.newEntity());
    entities.push_back(_instance.newEntity());

    initMapSize();
    posY = ((_map.size()-2)*100)+10;

    for (auto & it : _map) {
        for (char const &c: it) {
            randNb = std::rand()%2;
            if (c == '*') {
                CreateBlock(x, y, "../assets/blocks/Brick.jpeg", false);
            } else if (c == ' ' && !CheckIfSpawn(x, y, _map.size(), _map[0].size()) && randNb == 0) {
                it[x/100] = 'x';
                CreateBlock(x, y, "../assets/blocks/Wood.png", true);
            } else if (CheckIfBorder(x, y, _map.size(), _map[0].size()) && randNb != 0) {
                it[x/100] = 'x';
                CreateBlock(x, y, "../assets/blocks/Wood.png", true);
            }
            x += 100;
        }
        y += 100;
        x = 0;
    }

    if (_gameConfig.getCharsTypes().empty()) {
        _gameConfig.setCharsTypes(std::vector<PlayerType>({AI, AI, AI, AI}));
    }
    for (unsigned int i = 0; i != _gameConfig.getCharsTypes().size(); i++) {
        createCustomCharacter(i, posX, posY, !_gameConfig.getCharsTypes()[i]);
        posX += ((_map[0].size()-3)*100);
        if (posX > ((_map[0].size()-2)*100)+10) {
            posX = 110;
            posY -= ((_map.size()-3)*100);
        }
        if (posY < 110) {
            posY = ((_map.size()-1)*100) + 10;
        }
    }
    _mapName = IdGen::generateUUID(8);
    _isGameEnded = false;
    _gameConfig.setMap(nullptr, _mapName);
}

void SceneGame::initMapSize(bool newGame)
{
    _map.clear();
    switch (_config.getMapSize()) {
    case LARGE:
        _camera->setPosition(2100, 450, -2400);
        _camera->lookAt(2100, 1200, 0);
        if (newGame)
            _camera->getCamera()->addAnimator(_sceneManager->createFlyStraightAnimator({-1000, 0, 0}, {2100, 450, -2400}, 4000));

        _map.emplace_back("*********************************************");
        _map.emplace_back("*                                           *");
        _map.emplace_back("* * * * * * * * * * * * * * * * * * * * * * *");
        _map.emplace_back("*                                           *");
        _map.emplace_back("* * * * * * * * * * * * * * * * * * * * * * *");
        _map.emplace_back("*                                           *");
        _map.emplace_back("* * * * * * * * * * * * * * * * * * * * * * *");
        _map.emplace_back("*                                           *");
        _map.emplace_back("* * * * * * * * * * * * * * * * * * * * * * *");
        _map.emplace_back("*                                           *");
        _map.emplace_back("* * * * * * * * * * * * * * * * * * * * * * *");
        _map.emplace_back("*                                           *");
        _map.emplace_back("* * * * * * * * * * * * * * * * * * * * * * *");
        _map.emplace_back("*                                           *");
        _map.emplace_back("* * * * * * * * * * * * * * * * * * * * * * *");
        _map.emplace_back("*                                           *");
        _map.emplace_back("* * * * * * * * * * * * * * * * * * * * * * *");
        _map.emplace_back("*                                           *");
        _map.emplace_back("* * * * * * * * * * * * * * * * * * * * * * *");
        _map.emplace_back("*                                           *");
        _map.emplace_back("* * * * * * * * * * * * * * * * * * * * * * *");
        _map.emplace_back("*                                           *");
        _map.emplace_back("* * * * * * * * * * * * * * * * * * * * * * *");
        _map.emplace_back("*                                           *");
        _map.emplace_back("* * * * * * * * * * * * * * * * * * * * * * *");
        _map.emplace_back("*                                           *");
        _map.emplace_back("*********************************************");
        break;
    case MEDIUM:
        _camera->setPosition(1400, 300, -1600);
        _camera->lookAt(1400, 800, 0);
        if (newGame)
            _camera->getCamera()->addAnimator(_sceneManager->createFlyStraightAnimator({-1000, 0, 0}, {1400, 300, -1600}, 4000));

        _map.emplace_back("*****************************");
        _map.emplace_back("*                           *");
        _map.emplace_back("* * * * * * * * * * * * * * *");
        _map.emplace_back("*                           *");
        _map.emplace_back("* * * * * * * * * * * * * * *");
        _map.emplace_back("*                           *");
        _map.emplace_back("* * * * * * * * * * * * * * *");
        _map.emplace_back("*                           *");
        _map.emplace_back("* * * * * * * * * * * * * * *");
        _map.emplace_back("*                           *");
        _map.emplace_back("* * * * * * * * * * * * * * *");
        _map.emplace_back("*                           *");
        _map.emplace_back("* * * * * * * * * * * * * * *");
        _map.emplace_back("*                           *");
        _map.emplace_back("* * * * * * * * * * * * * * *");
        _map.emplace_back("*                           *");
        _map.emplace_back("* * * * * * * * * * * * * * *");
        _map.emplace_back("*                           *");
        _map.emplace_back("*****************************");
        break;
    default:
        _camera->setPosition(700, 150, -800);
        _camera->lookAt(700, 400, 0);
        if (newGame)
            _camera->getCamera()->addAnimator(_sceneManager->createFlyStraightAnimator({-1000, 0, 0}, {700, 150, -800}, 4000));
        _map.emplace_back("***************");
        _map.emplace_back("*             *");
        _map.emplace_back("* * * * * * * *");
        _map.emplace_back("*             *");
        _map.emplace_back("* * * * * * * *");
        _map.emplace_back("*             *");
        _map.emplace_back("* * * * * * * *");
        _map.emplace_back("*             *");
        _map.emplace_back("***************");
        break;
    }
}
