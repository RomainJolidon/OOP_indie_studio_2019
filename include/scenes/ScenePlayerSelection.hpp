/*
** EPITECH PROJECT, 2023
** ScenePlayerSelection
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_SCENEPLAYERSELECTION_HPP
#define BOMBERMAN_SCENEPLAYERSELECTION_HPP

#include "scenes/AScene.hpp"
#include "ECS/Components.hpp"
#include "ECS/Instance.hpp"
#include "ECS/Storage.hpp"
#include "ECS/ECSEntity.hpp"

class ScenePlayerSelection : public AScene
{
    public:
    ScenePlayerSelection(VisualManager &visualManager, Config &config,
        GameConfig &gameConfig
    );
    void oneCycleLoop() override;
    void selectChar(PlayerType& charType, unsigned int buttonId, unsigned int textId, int pos);
    void createAllEntities();
    void emptyAllEntities();
    void resetScene();
    void load() override ;
    void unload() override ;
    void createModels();
    ~ScenePlayerSelection();

    protected:
    private:
        Instance _instance;
        Storage<Model> _modelStorage;
        std::vector<PlayerType> charsTypes;
        std::vector<int> _buttonsIds;
        std::vector<int> _textsIds;
};

#endif //BOMBERMAN_SCENEPLAYERSELECTION_HPP
