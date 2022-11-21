/*
** EPITECH PROJECT, 2023
** SceneMenu
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_SCENEMENU_HPP
#define BOMBERMAN_SCENEMENU_HPP

#include "scenes/AScene.hpp"

class SceneMenu : public AScene
{
    public:
    SceneMenu(VisualManager &visualManager, Config &config,
        GameConfig &gameConfig
    );
    void oneCycleLoop() override ;
    void createAllEntities();
    void emptyAllEntities();
    void resetScene();
    void load() override ;
    void unload() override ;
    ~SceneMenu();

    protected:
    private:
        std::pair<irr::scene::IAnimatedMeshSceneNode *, irr::scene::IAnimatedMeshSceneNode *> _dancer;
};


#endif //BOMBERMAN_SCENEMENU_HPP
