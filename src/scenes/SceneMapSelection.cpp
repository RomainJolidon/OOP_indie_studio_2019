/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/


#include "scenes/SceneMapSelection.hpp"
#include <memory>

SceneMapSelection::SceneMapSelection(VisualManager &visualManager,
    Config &config, GameConfig &gameConfig
) : AScene(visualManager, config, gameConfig)
{
    createInterface();
}

void SceneMapSelection::createInterface()
{
    auto allMaps = loadAllMaps();
    std::list<std::string> mapNames;
    unsigned int id = IdGen::getNewId();

    for (auto &it: allMaps) {
        mapNames.push_back(it.first);
    }
    _GUIEnv->createSeletionList({860, 410, 1060, 610}, mapNames, [id, allMaps, this]() {
        int count = 0;
        int selected = reinterpret_cast<irr::gui::IGUIListBox *>(_GUIEnv->getGUIElement(id))->getSelected();

        for (auto & allMap : allMaps) {
            if (count == selected) {
                _gameConfig.setMap(allMap.second, allMap.first);
                break;
            }
            count++;
        }
    }, id);
    id = IdGen::getNewId();
    addText({900, 380, 1100, 410}, "Saved Map", false);
    addButton({500, 780, 800, 980}, nullptr, "SMALL", [&](){
        _config.playSoundEffect(VALIDATE);
        _config.setMapSize(SMALL);
    });
    addButton({800, 780, 1100, 980}, nullptr, "MEDIUM", [&](){
        _config.playSoundEffect(VALIDATE);
        _config.setMapSize(MEDIUM);
    });
    addButton({1100, 780, 1400, 980}, nullptr, "LARGE", [&](){
        _config.playSoundEffect(VALIDATE);
        _config.setMapSize(LARGE);
    });
    addButton({1720, 780, 1920, 980}, nullptr, "SELECT PLAYERS", [&](){
        _config.playSoundEffect(VALIDATE);
        _config.setSceneIndex(PLAYER_SELECTION);
    });
}

void SceneMapSelection::oneCycleLoop()
{
    display();
}

void SceneMapSelection::load()
{
    _GUIEnv->load();
    _camera->load();
    _visualManager.getDevice().setInputReceivingSceneManager(_sceneManager);
    _visualManager.getDevice().setEventReceiver(&_GUIEnv->getEventManager());
    _loaded = true;
    _gameConfig.setMap(nullptr, "");
}

void SceneMapSelection::unload()
{
    _GUIEnv->unload();
    _camera->unload();
    _loaded = false;
}

std::unordered_map<std::string, std::shared_ptr<JsonData>> SceneMapSelection::loadAllMaps() const
{
    JsonData maps = JsonParser::parseJson("../saves/maps.json", false);
    std::unordered_map<std::string, std::shared_ptr<JsonData>> mapList;
    std::shared_ptr<data_t> saveList = maps.getData();
    data_t *test;

    for (int i = 0; i < static_cast<list_t *>(saveList->value)->size; i++) {
        test = static_cast<data_t *>(get_data_at_pos(static_cast<list_t *>(saveList->value), i));

        mapList[get_attribute_of_key(test, "name")] = std::make_shared<JsonData>
            (maps.getObjectWithAttribute("name", get_attribute_of_key(test, "name")), "", false);
    }
    return (mapList);
}

SceneMapSelection::~SceneMapSelection()
{
}
