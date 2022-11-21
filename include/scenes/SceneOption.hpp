/*
** EPITECH PROJECT, 2023
** SceneOption
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_SCENEOPTION_HPP
#define BOMBERMAN_SCENEOPTION_HPP

#include <ITexture.h>
#include "scenes/AScene.hpp"

class SceneOption : public AScene
{
    public:
        SceneOption(VisualManager &visualManager, Config &config,
            GameConfig &gameConfig
        );
        void oneCycleLoop() override ;
        void createAllEntities();
        void emptyAllEntities();
        void load() override ;
        void unload() override ;
        void resetGame();

        ~SceneOption();
    protected:
    private:
        unsigned long long _textVolumeID;
};


#endif //BOMBERMAN_SCENEOPTION_HPP
