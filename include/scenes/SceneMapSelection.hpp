/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_SCENEMAPSELECTION_HPP
#define BOMBERMAN_SCENEMAPSELECTION_HPP

#include "scenes/AScene.hpp"
#include "config/JsonParser.hpp"

class SceneMapSelection: public AScene {
    public:
    SceneMapSelection(VisualManager &visualManager, Config &config,
        GameConfig &gameConfig);
    ~SceneMapSelection() ;
    void createInterface();
    void oneCycleLoop() override ;
    void load() override;
    void unload() override;
    std::unordered_map<std::string, std::shared_ptr<JsonData>> loadAllMaps() const;

    protected:
    private:
};

#endif //BOMBERMAN_SCENEMAPSELECTION_HPP
